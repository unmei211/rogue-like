#include "rogue/systems/move_control_system.h"

#include "iostream"
#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/transform_component.h"

// Maybe need walking component
static bool Filter(const Entity &entity) {
  return entity.Contains<MovementComponent>() && entity.Contains<TransformComponent>() &&
         entity.Contains<PlayerControlComponent>();
}

MoveControlSystem::MoveControlSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                     const Controls &controls)
    : ISystem(entity_manager, system_manager), controls_(controls) {}

void MoveControlSystem::OnUpdateEntity(Entity *entity) const {
  auto mc = entity->Get<MovementComponent>();
  // auto tc = entity->Get<TransformComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();
  if (mc->direction_ != ZeroVec2) {
    mc->direction_ = ZeroVec2;
  }

  if (controls_.IsPressed(pcc->up_button_)) {
    mc->direction_ = UpVec2;
  } else if (controls_.IsPressed(pcc->down_button_)) {
    mc->direction_ = DownVec2;
  } else if (controls_.IsPressed(pcc->left_button_)) {
    mc->direction_ = LeftVec2;
  } else if (controls_.IsPressed(pcc->right_button_)) {
    mc->direction_ = RightVec2;
  }
}

void MoveControlSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (Filter(entity)) {
      OnUpdateEntity(&entity);
    }
  }
}
