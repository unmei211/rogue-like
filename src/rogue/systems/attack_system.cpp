#include "rogue/systems/attack_system.h"

#include "rogue/components/tags/attack_tracker_component.h"
#include "rogue/systems/damage_system.h"

AttackSystem::AttackSystem(EntityManager *entity_manager, SystemManager *system_manager, EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void AttackSystem::OnUpdate() {
  LogPrint(tag_);
  auto target = entity_handler_->target_;

  for (auto enemy : entity_handler_->enemies_) {
    enemy->Get<AttackTrackerComponent>()->attack_him_ = nullptr;
    if (enemy->Get<TransformComponent>()->pos_.Distance(target->Get<TransformComponent>()->pos_) <= 1 &&
        target->Get<ActionComponent>()->acted_) {
      enemy->Get<AttackTrackerComponent>()->attack_him_ = target;
      GetSystemManager().Enable<DamageSystem>();
    }
  }
}
