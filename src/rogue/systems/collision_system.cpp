#include "rogue/systems/collision_system.h"

#include <list>

#include "lib/ecs/engine.h"
#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/entity-filters/filters.h"

class ISystem;

class PlayerRigidCollisionsSystem : ISystem {};

static bool Filter(const Entity &entity) {
  return (HasCollider(entity) && HasTransform(entity) && HasMovement(entity));
}

CollisionSystem::CollisionSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                 CollidersMap *const colliders_map)
    : ISystem(entity_manager, system_manager), colliders_map_(colliders_map) {}

static void Collide(Entity *entity, const std::list<Entity *> &applicants) {
  for (auto &app_entity : applicants) {
    if (app_entity->GetId() == entity->GetId()) {
      continue;
    }
    entity->Get<ColliderComponent>()->Collide(app_entity);
  }
}

void CollisionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (HasCollider(entity)) {
      entity.Get<ColliderComponent>()->Clear();
    }
  }
}

void CollisionSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (Filter(entity) && colliders_map_->GetSize(entity.Get<TransformComponent>()->pos_.VecToPos()) > 1) {
      Collide(&entity, colliders_map_->GetAllOnCage(entity.Get<TransformComponent>()->pos_.VecToPos()));
    }
  }
}
