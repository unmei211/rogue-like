#include "rogue/systems/take_coin_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/coin_component.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/wallet_component.h"

static bool FilterPlayer(const Entity& entity) {
  return entity.Contains<PlayerControlComponent>() && entity.Contains<LiftAbilityComponent>() &&
         entity.Contains<ColliderComponent>() && entity.Contains<WalletComponent>() &&
         entity.Get<ColliderComponent>()->AnyCollision();
}

static void GiveCoins(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (collision->Contains<CoinComponent>() && collision->Contains<TakeableComponent>()) {
      entity->Get<WalletComponent>()->moneys_ += collision->Get<CoinComponent>()->cost_;
      std::cout << "WWWWOOOOW" << std::endl;
      // DeleteCoin(entity);
    }
  }
}

TakeCoinSystem::TakeCoinSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

void TakeCoinSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (FilterPlayer(entity)) {
      GiveCoins(&entity);
      break;
    }
  }
}
