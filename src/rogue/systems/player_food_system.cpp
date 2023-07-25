#include "rogue/systems/player_food_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/entity-filters/filters.h"
PlayerFoodSystem::PlayerFoodSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void PlayerFoodSystem::OnUpdate() {
  for (auto &entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
    }
  }
}
