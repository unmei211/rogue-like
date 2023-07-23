#include "rogue/systems/take_coin_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/wallet_component.h"

static bool FilterPlayer(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>() && entity.Contains<LiftAbilityComponent>() &&
         entity.Contains<ColliderComponent>() && entity.Contains<WalletComponent>() &&
         entity.Get<ColliderComponent>()->AnyCollision();
}

void TakeCoinSystem::GiveCoins(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (collision->Contains<CostComponent>() && collision->Contains<TakeableComponent>()) {
      entity->Get<WalletComponent>()->moneys_ += collision->Get<CostComponent>()->cost_;
      std::cout << entity->Get<WalletComponent>()->moneys_ << std::endl;
      if (collision->Contains<RemovabilityComponent>()) {
        if (collision->Get<RemovabilityComponent>()->must_be_deleted_) {
          std::cout << "FATAL" << std::endl;
        }
        collision->Get<RemovabilityComponent>()->must_be_deleted_ = true;
        // test it: remove all except RemovabilityComponent
        // TODO: item_component
        std::cout << "GIVE COIN" << std::endl;
        // GetEntityManager().DeleteEntity(collision->GetId());
      }
    }
  }
}

TakeCoinSystem::TakeCoinSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

void TakeCoinSystem::OnUpdate() {
  // LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (FilterPlayer(entity)) {
      GiveCoins(&entity);
    }
  }
}
