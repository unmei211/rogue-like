#include "rogue/systems/collision_system.h"

#include <vector>

#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/transform_component.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<TransformComponent>();
}

CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

static void Collide(Entity* entity_1, Entity* entity_2) {
  auto cc2 = entity_2->Get<ColliderComponent>();

  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();

  if (ToPos(tc1->pos_.x_) == ToPos(tc2->pos_.x_) && ToPos(tc1->pos_.y_) == ToPos(tc2->pos_.y_)) {
    cc2->Collide(entity_1);
    std::cout << "COLLIDE!!! "  << std::endl;
  }
}

void CollisionSystem::OnUpdate() {
  std::vector<Entity*> may_collide;
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      entity.Get<ColliderComponent>()->Clear();
      may_collide.push_back(&entity);
    }
  }

  // TODO: fix O(n^2)
  for (auto& entity_1 : may_collide) {
    for (auto& entity_2 : may_collide) {
      if (entity_1->GetId() != entity_2->GetId()) {
        Collide(entity_1, entity_2);
      }
    }
  }
}
