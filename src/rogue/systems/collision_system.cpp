#include "rogue/systems/collision_system.h"

#include <vector>

#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "lib/utils/ignore_entity.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/transform_component.h"

static bool Filter(const Entity& entity) {
  bool match = false;
  if (entity.Contains<ColliderComponent>() && entity.Contains<TransformComponent>()) {
    match = true;
  }
  Ignore(entity);
  return match;
}

CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

static void Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }
  auto cc2 = entity_2->Get<ColliderComponent>();

  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();

  if (ToPos(tc1->pos_.x_) == ToPos(tc2->pos_.x_) && ToPos(tc1->pos_.y_) == ToPos(tc2->pos_.y_)) {
    cc2->Collide(entity_1);
    std::cout << "COLLIDE!!! " << entity_2->GetId() << " " << entity_1->GetId() << std::endl;
  }
}

void CollisionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<ColliderComponent>()) {
      entity.Get<ColliderComponent>()->Clear();
    }
  }
}

void CollisionSystem::OnUpdate() {
  LogPrint(tag_);
  //  std::cout << "COLLISION ON UPDATE " << std::endl;
  //  std::vector<Entity*> may_collide;
  //  for (auto& entity : GetEntityManager()) {
  //    if (Filter(entity)) {
  //      entity.Get<ColliderComponent>()->Clear();
  //      may_collide.push_back(&entity);
  //    }
  //  }
  //
  //  // TODO: fix O(n^2)
  //  for (auto& entity_1 : may_collide) {
  //    for (auto& entity_2 : may_collide) {
  //      if (entity_1->GetId() != entity_2->GetId()) {
  //        Collide(entity_1, entity_2);
  //      }
  //    }
  //  }

  // TODO: fix O(n^2)
  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (Filter(entity_2)) {
          Collide(&entity_1, &entity_2);
        }
      }
    }
  }
}
