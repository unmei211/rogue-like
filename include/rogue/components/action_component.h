#ifndef INCLUDE_ROGUE_COMPONENTS_ACTION_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ACTION_COMPONENT_H_

#include "lib/ecs/component.h"
class ActionComponent : public IComponent {
 public:
  explicit ActionComponent(bool acted = false) : acted_(acted) {}
  bool acted_;
  Vec2 old_direction_;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ACTION_COMPONENT_H_
