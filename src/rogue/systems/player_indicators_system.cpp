#include "rogue/systems/player_indicators_system.h"

#include "rogue/entity-filters/filters.h"

PlayerIndicatorsSystem::PlayerIndicatorsSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                               EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void PlayerIndicatorsSystem::OnStepsUpdate(Entity *entity) {
  if (HasMovement(*entity) && entity->Get<MovementComponent>()->direction_ != ZeroVec2 &&
      !entity->Get<RigidBodyComponent>()->AnyRigidCollisions()) {
    if (HasStomach(*entity) && entity->Get<StomachComponent>()->IsEmpty()) {
      entity->Get<HPComponent>()->heal_point_ -= 2;
    }
    entity->Get<MovementsCountComponent>()->count_++;
    entity->Get<MovementsCountComponent>()->aviable_steps_--;
  }
}

void PlayerIndicatorsSystem::OnUpdate() {
  LogPrint(tag_);
  OnStepsUpdate(entity_handler_->player_);
}
