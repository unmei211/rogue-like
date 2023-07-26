#ifndef INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_

#include "lib/ecs/component.h"
class HPComponent : IComponent {
 public:
  int heal_point_;
  explicit HPComponent(int heal_point = 100) : heal_point_(heal_point) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_
