#include "rogue/systems/collision_system.h"

#include "lib/ecs/engine.h"
#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/entity-filters/filters.h"

class ISystem;

class TakesSystem : ISystem {};
class TakeCoinSystem : ISystem {};
class PlayerRigidCollisionSystem : ISystem {};

static bool Filter(const Entity& entity) {
  return (HasCollider(entity) && HasTransform(entity));
}

CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

static bool Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return false;
  }
  auto cc2 = entity_2->Get<ColliderComponent>();

  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();

  if (ToPos(tc1->pos_.x_) == ToPos(tc2->pos_.x_) && ToPos(tc1->pos_.y_) == ToPos(tc2->pos_.y_)) {
    cc2->Collide(entity_1);
    return true;
  }
  return false;
}

void CollisionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasCollider(entity)) {
      entity.Get<ColliderComponent>()->Clear();
    }
  }
}

void CollisionSystem::OnUpdate() {
  LogPrint(tag_);
  bool any = false;
  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (Filter(entity_2) && Collide(&entity_1, &entity_2)) {
          any = true;
        }
      }
    }
  }
  if (!any) {
    GetSystemManager().Disable<TakesSystem>();
    GetSystemManager().Disable<TakeCoinSystem>();
    // GetSystemManager().Disable<PlayerRigidCollisionSystem>();
  } else {
    GetSystemManager().Enable<TakesSystem>();
    GetSystemManager().Enable<TakeCoinSystem>();
    // GetSystemManager().Enable<PlayerRigidCollisionSystem>();
  }
}
