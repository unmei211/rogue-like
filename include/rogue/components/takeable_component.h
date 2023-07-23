#ifndef INCLUDE_ROGUE_COMPONENTS_TAKEABLE_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_TAKEABLE_COMPONENT_H_

#include "lib/ecs/component.h"
class TakeableComponent : public IComponent {
 public:
  bool picked_up_;
  explicit TakeableComponent(bool picked_up = false) : picked_up_(picked_up) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_TAKEABLE_COMPONENT_H_
