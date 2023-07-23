#ifndef INCLUDE_ROGUE_COMPONENTS_DURABILITY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_DURABILITY_COMPONENT_H_

#include "lib/ecs/component.h"
class DurabilityComponent : public IComponent {
 public:
  int full_durability_;
  int current_durability_;

  DurabilityComponent(int full_durability, int current_durability)
      : full_durability_(full_durability), current_durability_(current_durability) {}
  explicit DurabilityComponent(int full_durability)
      : full_durability_(full_durability), current_durability_(full_durability) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_DURABILITY_COMPONENT_H_
