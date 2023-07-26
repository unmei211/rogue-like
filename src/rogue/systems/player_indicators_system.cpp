#include "rogue/systems/player_indicators_system.h"

#include "rogue/entity-filters/filters.h"

PlayerIndicatorsSystem::PlayerIndicatorsSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void PlayerIndicatorsSystem::OnStepsUpdate(Entity *entity) {
  if (entity->Get<MovementComponent>()->direction_ != ZeroVec2 &&
      !entity->Get<RigidBodyComponent>()->AnyRigidCollisions()) {
    entity->Get<MovementsCountComponent>()->count_++;
    entity->Get<MovementsCountComponent>()->aviable_steps_--;
  }
}

void PlayerIndicatorsSystem::OnUpdate() {
  for (auto &entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
      OnStepsUpdate(&entity);
    }
  }
}
