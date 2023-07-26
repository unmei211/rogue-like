#include "rogue/systems/player_rigid_collisions_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/entity-filters/filters.h"

PlayerRigidCollisionsSystem::PlayerRigidCollisionsSystem(EntityManager* const entity_manager,
                                                         SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

void PlayerRigidCollisionsSystem::OnRigidCollisions(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  if (!cc->AnyCollision()) {
    return;
  }

  for (auto& collision : cc->GetCollisions()) {
    if (HasRigidBody(*collision) && collision->Get<RigidBodyComponent>()->is_rigid_) {
      entity->Get<RigidBodyComponent>()->RigidCollide(collision);
      entity->Get<MovementComponent>()->direction_ *= -1;
      entity->Get<TransformComponent>()->pos_ += entity->Get<MovementComponent>()->direction_;
    }
  }
}

void PlayerRigidCollisionsSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
      entity.Get<RigidBodyComponent>()->Clear();
    }
  }

  for (auto& entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
      OnRigidCollisions(&entity);
    }
  }
}
