#include "rogue/systems/rigid_collisions_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/attributes/rigid_body_component.h"
#include "rogue/entity-filters/filters.h"

RigidCollisionsSystem::RigidCollisionsSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                             EntityMap* const entity_map)
    : ISystem(entity_manager, system_manager), entity_map_(entity_map) {}

void RigidCollisionsSystem::OnRigidCollisions(Entity* entity) {
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
      entity_map_->MoveTo(tc->pos_.VecToPos() + mc->direction_ * -1, tc->pos_.VecToPos(), entity);
      entity->Get<MovementComponent>()->direction_ *= -1;
      entity->Get<TransformComponent>()->pos_ += entity->Get<MovementComponent>()->direction_;
      entity->Get<MovementComponent>()->direction_ = ZeroVec2;
    } else if (HasRigidBody(*collision) && collision->Get<RigidBodyComponent>()->is_rigid_) {
      auto mc = entity->Get<MovementComponent>();
      auto tc = entity->Get<TransformComponent>();
      auto rbc = entity->Get<RigidBodyComponent>();
      rbc->RigidCollide(collision);
      entity_map_->MoveTo(tc->pos_.VecToPos() + mc->direction_ * -1, tc->pos_.VecToPos(), entity);
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
