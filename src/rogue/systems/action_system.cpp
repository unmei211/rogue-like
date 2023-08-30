#include "rogue/systems/action_system.h"

ActionSystem::ActionSystem(EntityManager *entity_manager, SystemManager *system_manager, EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void ActionSystem::OnPreUpdate() {
  LogPrint(tag_);
  entity_handler_->having_control_->Get<ActionComponent>()->acted_ = false;
}
