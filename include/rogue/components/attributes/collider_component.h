#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLLIDER_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLLIDER_COMPONENT_H_

#include <list>
#include <set>

#include "lib/ecs/component.h"
#include "lib/math/vec2.h"
class Entity;

class ColliderComponent : public IComponent {
  std::set<Entity*> collisions_{};

 public:
  Vec2 size_;
  Vec2 offset_;

  explicit ColliderComponent(const Vec2& size, const Vec2& offset = ZeroVec2) : size_(size), offset_(offset) {}

  const std::set<Entity*>& GetCollisions() const {
    return collisions_;
  }

  bool AnyCollision() const {
    return !collisions_.empty();
  }

  template<typename Component>
  std::list<Entity*> GetListCollisionsOfType() {
    std::list<Entity*> temp_list;
    for (auto& collision : collisions_) {
      if (collision->Contains<Component>()) {
        temp_list.push_back(collision);
      }
    }
    return temp_list;
  }

  void Collide(Entity* entity) {
    collisions_.insert(entity);
  }

  void Clear() {
    collisions_.clear();
  }
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLLIDER_COMPONENT_H_
