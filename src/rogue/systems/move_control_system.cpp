#include "rogue/systems/move_control_system.h"

#include "iostream"
#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/components/capabilities/movement_component.h"
#include "rogue/components/capabilities/player_control_component.h"
#include "rogue/entity-filters/filters.h"

MoveControlSystem::MoveControlSystem(EntityManager* entity_manager, SystemManager* system_manager,
                                     const Controls& controls, EntityHandler* entity_handler)
    : ISystem(entity_manager, system_manager), controls_(controls), entity_handler_(entity_handler) {}

void MoveControlSystem::OnUpdateEntity(Entity* entity) const {
  if (!(HasMovement(*entity) && HasTransform(*entity))) {
    return;
  }
  auto mc = entity->Get<MovementComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();
  if (mc->direction_ != ZeroVec2) {
    mc->direction_ = ZeroVec2;
  }
  auto action = entity->Get<ActionComponent>();
  if (controls_.IsPressed(pcc->up_button_)) {
    mc->direction_ = UpVec2;
    action->acted_ = true;
  } else if (controls_.IsPressed(pcc->down_button_)) {
    mc->direction_ = DownVec2;
    action->acted_ = true;
  } else if (controls_.IsPressed(pcc->left_button_)) {
    mc->direction_ = LeftVec2;
    action->acted_ = true;
  } else if (controls_.IsPressed(pcc->right_button_)) {
    mc->direction_ = RightVec2;
    action->acted_ = true;
  }
  if (mc->direction_ != ZeroVec2 && entity->Contains<ActionComponent>()) {
    entity->Get<ActionComponent>()->old_direction_ = entity->Get<MovementComponent>()->direction_;
  }
}

void MoveControlSystem::OnUpdate() {
  LogPrint(tag_);
  OnUpdateEntity(entity_handler_->having_control_);
}
