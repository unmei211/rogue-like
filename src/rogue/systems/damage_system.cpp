#include "rogue/systems/damage_system.h"

#include "lib/ecs/system_manager.h"
#include "rogue/components/tags/attack_tracker_component.h"
DamageSystem::DamageSystem(EntityManager *entity_manager, SystemManager *system_manager, EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void DamageSystem::OnUpdate() {
  LogPrint(tag_);
  auto target = entity_handler_->target_;
  for (auto enemy : entity_handler_->enemies_) {
    auto atc = enemy->Get<AttackTrackerComponent>();
    if (atc->attack_him_ != nullptr && atc->attack_him_->GetId() == target->GetId()) {
      target->Get<HPComponent>()->heal_point_ -= enemy->Get<DamageComponent>()->damage_;
    }
    if (IsPlayer(*target) && target->Get<RigidBodyComponent>()->CollisionWithID(enemy->GetId())) {
      enemy->Get<HPComponent>()->heal_point_ -= target->Get<DamageComponent>()->damage_;
      if (enemy->Get<HPComponent>()->heal_point_ <= 0) {
        enemy->Add<RemovabilityComponent>();
        enemy->Delete<EnemyComponent>();
        entity_handler_->enemies_.erase(enemy);
        return;
      }
    }
    if (target->Get<HPComponent>()->heal_point_ <= 0 && !IsPlayer(*target)) {
      target->Delete<TargetComponent>();
      entity_handler_->target_ = entity_handler_->player_;
      target->Add<TargetComponent>();
    }
  }
  GetSystemManager().Disable<DamageSystem>();
}
