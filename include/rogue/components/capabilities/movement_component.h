#ifndef INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_MOVEMENT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_MOVEMENT_COMPONENT_H_

#include "lib/ecs/component.h"
#include "lib/math/vec2.h"

class MovementComponent : public IComponent {
 public:
  Vec2 speed_;
  Vec2 direction_;
  explicit MovementComponent(Vec2 speed, Vec2 direction = ZeroVec2) : speed_(speed), direction_(direction) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_MOVEMENT_COMPONENT_H_
