#include "rogue/systems/take_food_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/breakable_component.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/item_component.h"
#include "rogue/components/tags/loot_component.h"
#include "rogue/entity-filters/filters.h"

static bool Filter(const Entity& entity) {
  return IsPlayer(entity);
}

TakeFoodSystem::TakeFoodSystem(EntityManager* entity_manager, SystemManager* system_manager)
    : ISystem(entity_manager, system_manager) {}

void TakeFoodSystem::GiveFood(Entity* entity) {
  if (!(HasLiftAbility(*entity) && HasStomach(*entity) && entity->Get<LiftAbilityComponent>()->AnyPicked())) {
    return;
  }
  auto lac = entity->Get<LiftAbilityComponent>();
  for (auto& item : lac->GetHandPicked()) {
    if (IsFood(*item) && !IsItem(*item)) {
      item->Delete<TransformComponent>();
      item->Delete<ColliderComponent>();
      item->Delete<TakeableComponent>();
      item->Delete<LootComponent>();
      item->Add<ItemComponent>();

      entity->Get<StomachComponent>()->AddFood(item);
      //      // TODO добавление персонажу
    }
  }
}

void TakeFoodSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      GiveFood(&entity);
    }
  }
}
