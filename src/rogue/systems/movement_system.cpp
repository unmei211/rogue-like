#include "rogue/systems/movement_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/components/attributes/transform_component.h"
#include "rogue/components/capabilities/movement_component.h"
#include "rogue/entity-filters/filters.h"

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               EntityMap* const entity_map)
    : ISystem(entity_manager, system_manager), entity_map_(entity_map) {}
void MovementSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasMovement(entity) && HasTransform(entity)) {
      auto tc = entity.Get<TransformComponent>();
      auto mc = entity.Get<MovementComponent>();
      Vec2 old_pos = tc->pos_.VecToPos();
      tc->pos_ += mc->direction_ * mc->speed_;
      if (old_pos != tc->pos_.VecToPos()) {
        entity_map_->MoveTo(tc->pos_.VecToPos(), old_pos, &entity);
      }
    }
  }
}
