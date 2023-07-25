#include "rogue/systems/take_coin_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/wallet_component.h"


static bool Filter(const Entity& entity) {
  return entity.Contains<PlayerComponent>();
}

void TakeCoinSystem::GiveCoins(Entity* entity) {
  if (!(entity->Contains<LiftAbilityComponent>() && entity->Contains<ColliderComponent>() &&
        entity->Contains<WalletComponent>() && entity->Get<ColliderComponent>()->AnyCollision())) {
    return;
  }
  auto cc = entity->Get<LiftAbilityComponent>();
  for (auto& item : cc->GetHandPicked()) {
    if (item->Contains<CoinComponent>()) {
      entity->Get<WalletComponent>()->moneys_ += item->Get<CostComponent>()->cost_;
      std::cout << entity->Get<WalletComponent>()->moneys_ << std::endl;
    }
  }
}

TakeCoinSystem::TakeCoinSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

void TakeCoinSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      GiveCoins(&entity);
    }
  }
}
