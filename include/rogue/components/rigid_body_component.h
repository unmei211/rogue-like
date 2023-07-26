#ifndef INCLUDE_ROGUE_COMPONENTS_RIGID_BODY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_RIGID_BODY_COMPONENT_H_
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

  void RigidCollide(Entity* entity) {
    rigid_collisions_.insert(entity);
  }

  const std::set<Entity*>& GetRigidCollisions() const {
    return rigid_collisions_;
  }

  explicit RigidBodyComponent(bool is_rigid = true) : is_rigid_(is_rigid) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_RIGID_BODY_COMPONENT_H_
