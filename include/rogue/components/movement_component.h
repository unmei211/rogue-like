#ifndef INCLUDE_ROGUE_COMPONENTS_MOVEMENT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_MOVEMENT_COMPONENT_H_

#include "lib/ecs/component.h"
#include "lib/math/vec2.h"

class MovementComponent : public IComponent {
 public:
  Vec2 direction_;
  explicit MovementComponent(Vec2 direction = ZeroVec2) : direction_(direction) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_MOVEMENT_COMPONENT_H_
