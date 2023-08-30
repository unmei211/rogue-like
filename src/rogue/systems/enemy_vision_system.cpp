#include "rogue/systems/enemy_vision_system.h"

class TargetingSystem : public ISystem {};
EnemyVisionSystem::EnemyVisionSystem(EntityManager *entity_manager, SystemManager *system_manager,
                                     EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void EnemyVisionSystem::OnUpdate() {
  LogPrint(tag_);
  {
    auto target = entity_handler_->target_;
    if (entity_handler_->enemies_.empty() || target == nullptr) {
      return;
    }
  }
  auto target_pos = entity_handler_->target_->Get<TransformComponent>()->pos_.VecToPos();
  for (auto enemy : entity_handler_->enemies_) {
    if (enemy == nullptr) {
      entity_handler_->enemies_.erase(enemy);
      continue;
    }
    if (ToPos(target_pos.Distance(enemy->Get<TransformComponent>()->pos_.VecToPos())) <=
            enemy->Get<VisionComponent>()->distance_ &&
        entity_handler_->target_->Get<ActionComponent>()->acted_) {
      GetSystemManager().Enable<TargetingSystem>();
    } else {
      enemy->Get<MovementComponent>()->direction_ = ZeroVec2;
    }
  }
}
