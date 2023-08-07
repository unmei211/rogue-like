#ifndef INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_

#include "lib/ecs/component.h"
class HPComponent : public IComponent {
 public:
  int heal_point_;
  int max_heal_point_;
  explicit HPComponent(int heal_point = 100, int max_heal_point = 100)
      : heal_point_(heal_point), max_heal_point_(max_heal_point) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_HP_COMPONENT_H_
