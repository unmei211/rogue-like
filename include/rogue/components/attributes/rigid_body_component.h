#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_RIGID_BODY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_RIGID_BODY_COMPONENT_H_
#include <set>

#include "lib/ecs/component.h"
class RigidBodyComponent : public IComponent {
  std::set<Entity*> rigid_collisions_{};

 public:
  bool is_rigid_;
  void Clear() {
    rigid_collisions_.clear();
  }
  bool AnyRigidCollisions() const {
    return !rigid_collisions_.empty();
  }

  bool ContainsRigidBodyCollision() {
    for (auto e : rigid_collisions_) {
      if (e->Get<RigidBodyComponent>()->is_rigid_) {
        return true;
      }
    }
    return false;
  }

  void DeleteCollisionWithID(size_t ID) {
    if (!AnyRigidCollisions()) {
      return;
    }
    auto collisions = GetRigidCollisions();
    for (auto entity : collisions) {
      if (entity->GetId() == ID) {
        collisions.erase(entity);
      }
    }
  }
  void RigidCollide(Entity* entity) {
    rigid_collisions_.insert(entity);
  }
  template<typename Component>
  bool CollisionWith() {
    if (!AnyRigidCollisions()) {
      return false;
    }
    auto collisions = GetRigidCollisions();
    for (auto entity : collisions) {
      if (entity->Contains<Component>()) {
        return true;
      }
    }
    return false;
  }
  [[nodiscard]] bool CollisionWithID(size_t ID) const {
    if (!AnyRigidCollisions()) {
      return false;
    }
    auto collisions = GetRigidCollisions();
    for (auto entity : collisions) {
      if (entity->GetId() == ID) {
        return true;
      }
    }
    return false;
  }
  const std::set<Entity*>& GetRigidCollisions() const {
    return rigid_collisions_;
  }

  explicit RigidBodyComponent(bool is_rigid = true) : is_rigid_(is_rigid) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_RIGID_BODY_COMPONENT_H_
