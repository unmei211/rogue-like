#include "rogue/systems/ability_control_system.h"

#include "rogue/entity-filters/filters.h"

static bool Filter(const Entity* entity) {
  return HasPlayerControl(*entity);
}

AbilityControlSystem::AbilityControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                           const Controls& controls)
    : ISystem(entity_manager, system_manager), controls_(controls) {}

void AbilityControlSystem::OnUpdateEntity(Entity* entity) const {
  auto pcc = entity->Get<PlayerControlComponent>();
  if (HasStomach(*entity)) {
    if (controls_.IsPressed(pcc->switch_food_button_)) {
      entity->Get<StomachComponent>()->Switch();
    }
  }
}

void AbilityControlSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (Filter(&entity)) {
      OnUpdateEntity(&entity);
    }
  }
}
