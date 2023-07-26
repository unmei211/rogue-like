#include "rogue/systems/movement_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/entity-filters/filters.h"
MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
void MovementSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasMovement(entity) && HasTransform(entity)) {
      auto tc = entity.Get<TransformComponent>();
      auto mc = entity.Get<MovementComponent>();

      tc->pos_ += mc->direction_ * mc->speed_;
    }
  }
}
