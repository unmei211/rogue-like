#include "rogue/systems/floor_traps_system.h"

#include <vector>

#include "rogue/math/Rand.h"
void FloorTrapsSystem::CheckDamage() {
  std::vector<Entity *> to_delete_;
  for (auto &enemy : entity_handler_->enemies_) {
    if (enemy->Contains<RemovabilityComponent>()) {
      continue;
    }
    auto traps = enemy->Get<ColliderComponent>()->GetListCollisionsOfType<TrapComponent>();
    if (traps.empty() ||
        (!traps.front()->Contains<LootComponent>() && traps.front()->Get<TrapComponent>()->GetState() != 2)) {
      continue;
    }
    if (traps.empty() ||
        (traps.front()->Contains<LootComponent>() && traps.front()->Get<TrapComponent>()->GetState() == 0)) {
      continue;
    }

    auto hpc = enemy->Get<HPComponent>();
    hpc->heal_point_ -= traps.front()->Get<DamageComponent>()->damage_;

    if (hpc->heal_point_ <= 0) {
      to_delete_.push_back(enemy);
      enemy->Add<RemovabilityComponent>();
      if (!enemy->Contains<EnemyComponent>()) {
      } else {
      }
    }
    if (traps.front()->Contains<LootComponent>()) {
      // traps.front()->Delete<TextureComponent>();
      to_delete_.push_back(traps.front());
      //      entity_handler_->traps_.erase(traps.front());
      traps.front()->Add<RemovabilityComponent>();
    }
  }
  for (auto en : to_delete_) {
    if (en->Contains<EnemyComponent>()) {
      entity_handler_->enemies_.erase(en);
    } else if (en->Contains<TrapComponent>()) {
      entity_handler_->traps_.erase(en);
    }
  }

  auto hc = entity_handler_->having_control_;
  auto cc = entity_handler_->having_control_->Get<ColliderComponent>();
  auto traps = cc->GetListCollisionsOfType<TrapComponent>();
  if (traps.empty() ||
      (!traps.front()->Contains<LootComponent>() && traps.front()->Get<TrapComponent>()->GetState() != 2)) {
    return;
  }
  if (traps.empty() ||
      (traps.front()->Contains<LootComponent>() && traps.front()->Get<TrapComponent>()->GetState() == 0)) {
    return;
  }
  hc->Get<HPComponent>()->heal_point_ -= traps.front()->Get<DamageComponent>()->damage_;
  if (traps.front()->Contains<LootComponent>()) {
    traps.front()->Add<RemovabilityComponent>();
    traps.front()->Delete<TrapComponent>();
    if (entity_handler_->having_control_->Contains<FoodComponent>()) {
      entity_handler_->having_control_->Get<HPComponent>()->heal_point_ -= 100;
    }
    // traps.front()->Delete<TextureComponent>();
    entity_handler_->traps_.erase(traps.front());
  }
}

void FloorTrapsSystem::OnTrapsUpdate() {
  for (auto &trap : entity_handler_->traps_) {
    auto trap_component = trap->Get<TrapComponent>();
    if (trap->Contains<LootComponent>()) {
      if (trap_component->GetState() == 0) {
        trap_component->steps_activity_--;
        if (trap_component->steps_activity_ <= 0) {
          trap->Delete<TakeableComponent>();
          trap_component->ToForward();
          trap_component->steps_activity_ = Rand(2, 6);
        }
      }
      //      if (trap_component->GetState() == 0 && Rand(0, 4) == 4) {
      //        trap->Delete<TakeableComponent>();
      //        trap_component->ToForward();
      //        trap_component->steps_activity_ = Rand(2, 6);
      //      }
      else if (trap_component->GetState() == 2) {
        trap_component->steps_activity_ -= 1;
        if (trap_component->steps_activity_ <= 0) {
          trap_component->ToReady();
        }
      } else if (trap_component->GetState() == 1) {
        trap->Add<TakeableComponent>();
        trap_component->ToClose();
        trap_component->steps_activity_ = Rand(1, 4);
      }
    } else {
      if (trap_component->GetState() == 0 && Rand(0, 4) == 4) {
        trap_component->ToReady();
      } else if (trap_component->GetState() == 1) {
        trap_component->ToForward();
        trap_component->steps_activity_ = Rand(2, 6);
      } else if (trap_component->GetState() == 2) {
        trap_component->steps_activity_ -= 1;
        if (trap_component->steps_activity_ <= 0) {
          trap_component->ToClose();
        }
      }
    }
  }
  CheckDamage();
}

void FloorTrapsSystem::OnUpdate() {
  LogPrint(tag_);
  if (entity_handler_->having_control_->Get<ActionComponent>()->acted_ &&
      entity_handler_->having_control_->Get<MovementComponent>()->direction_ != ZeroVec2) {
    OnTrapsUpdate();
  }
}
