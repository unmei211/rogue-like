#include "rogue/systems/player_indicators_system.h"

#include <string>

#include "rogue/entity-filters/filters.h"
PlayerIndicatorsSystem::PlayerIndicatorsSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                               EntityHandler *entity_handler, const std::string &level_name)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler), level_name_(level_name) {}

void PlayerIndicatorsSystem::OnStepsUpdate(Entity *entity) {
  if (HasMovement(*entity) && entity->Get<MovementComponent>()->direction_ != ZeroVec2 &&
      !entity->Get<RigidBodyComponent>()->AnyRigidCollisions()) {
    if (HasStomach(*entity) && entity->Get<StomachComponent>()->IsEmpty()) {
      entity->Get<HPComponent>()->heal_point_ -= 2;
    }
    if (level_name_ != LEVEL_RANDOM_NAME) {
      entity->Get<MovementsCountComponent>()->count_++;
      entity->Get<MovementsCountComponent>()->aviable_steps_--;
    }
  }
}

void PlayerIndicatorsSystem::OnUpdate() {
  LogPrint(tag_);
  OnStepsUpdate(entity_handler_->player_);
}
