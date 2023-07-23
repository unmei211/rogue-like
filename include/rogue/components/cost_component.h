#ifndef INCLUDE_ROGUE_COMPONENTS_COST_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_COST_COMPONENT_H_

#include "lib/ecs/component.h"
class CostComponent : public IComponent {
 public:
  unsigned int cost_;
  explicit CostComponent(unsigned int cost = 5) : cost_(cost) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_COST_COMPONENT_H_
