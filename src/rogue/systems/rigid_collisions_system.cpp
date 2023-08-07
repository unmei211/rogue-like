#include "rogue/systems/rigid_collisions_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/entity-filters/filters.h"

RigidCollisionsSystem::RigidCollisionsSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                             CollidersMap* const colliders_map)
    : ISystem(entity_manager, system_manager), colliders_map_(colliders_map) {}

void RigidCollisionsSystem::OnRigidCollisions(Entity* entity) {
  if (!HasRigidBody(*entity)) {
    return;
  }
  auto cc = entity->Get<ColliderComponent>();
  if (!cc->AnyCollision()) {
    return;
  }
  auto entity_rigid = entity->Get<RigidBodyComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (entity_rigid->is_rigid_ && HasRigidBody(*collision) && collision->Get<RigidBodyComponent>()->is_rigid_) {
      auto mc = entity->Get<MovementComponent>();
      auto tc = entity->Get<TransformComponent>();
      auto rbc = entity->Get<RigidBodyComponent>();
      rbc->RigidCollide(collision);
      if (collision->Get<RigidBodyComponent>()->CollisionWithID(entity->GetId())) {
        continue;
      }
      colliders_map_->MoveTo(tc->pos_.VecToPos() + mc->direction_ * -1, tc->pos_.VecToPos(), entity);
      entity->Get<MovementComponent>()->direction_ *= -1;
      entity->Get<TransformComponent>()->pos_ += entity->Get<MovementComponent>()->direction_;
      entity->Get<MovementComponent>()->direction_ = ZeroVec2;
    } else if (HasRigidBody(*collision) && collision->Get<RigidBodyComponent>()->is_rigid_) {
      auto mc = entity->Get<MovementComponent>();
      auto tc = entity->Get<TransformComponent>();
      auto rbc = entity->Get<RigidBodyComponent>();
      rbc->RigidCollide(collision);
      colliders_map_->MoveTo(tc->pos_.VecToPos() + mc->direction_ * -1, tc->pos_.VecToPos(), entity);
      entity->Get<MovementComponent>()->direction_ *= -1;
      entity->Get<TransformComponent>()->pos_ += entity->Get<MovementComponent>()->direction_;
      entity->Get<MovementComponent>()->direction_ = ZeroVec2;
    }
  }
}

void RigidCollisionsSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasMovement(entity) && HasRigidBody(entity)) {
      entity.Get<RigidBodyComponent>()->Clear();
    }
  }
}

void RigidCollisionsSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (HasMovement(entity) && HasRigidBody(entity)) {
      OnRigidCollisions(&entity);
    }
  }
}
