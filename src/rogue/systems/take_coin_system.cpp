#include "rogue/systems/take_coin_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/attributes/wallet_component.h"
#include "rogue/components/capabilities/lift_ability_component.h"
#include "rogue/components/indicators/cost_component.h"
#include "rogue/entity-filters/filters.h"

static bool Filter(const Entity& entity) {
  return HasLiftAbility(entity);
}

void TakeCoinSystem::GiveCoins(Entity* entity) {
  if (!(HasLiftAbility(*entity) && HasWallet(*entity) && entity->Get<LiftAbilityComponent>()->AnyPicked())) {
    return;
  }
  auto lac = entity->Get<LiftAbilityComponent>();
  for (auto& item : lac->GetHandPicked()) {
    if (IsCoin(*item)) {
      entity->Get<WalletComponent>()->moneys_ += item->Get<CostComponent>()->cost_;
      item->Add<RemovabilityComponent>();
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
