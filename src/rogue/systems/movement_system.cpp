#include "rogue/systems/movement_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/counters/movements_count_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/transform_component.h"

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
void MovementSystem::OnUpdate() {
  // LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<MovementComponent>() && entity.Contains<TransformComponent>()) {
      auto tc = entity.Get<TransformComponent>();
      auto mc = entity.Get<MovementComponent>();

      tc->pos_ += mc->direction_ * mc->speed_;
      if (entity.Contains<MovementsCountComponent>() && entity.Get<MovementComponent>()->direction_ != ZeroVec2) {
        entity.Get<MovementsCountComponent>()->count++;
      }
    }
  }
}
