#include "rogue/systems/movement_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/entity-filters/filters.h"

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               CollidersMap* const colliders_map)
    : ISystem(entity_manager, system_manager), colliders_map_(colliders_map) {}
void MovementSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasMovement(entity) && HasTransform(entity)) {
      auto tc = entity.Get<TransformComponent>();
      auto mc = entity.Get<MovementComponent>();
      if (HasCollider(entity)) {
        Vec2 old_pos = tc->pos_.VecToPos();
        Vec2 new_pos = (tc->pos_ + mc->direction_ * mc->speed_).VecToPos();
        if (old_pos != new_pos) {
          colliders_map_->MoveTo(new_pos, old_pos, &entity);
        }
      }
      tc->pos_ += mc->direction_ * mc->speed_;
    }
  }
}
