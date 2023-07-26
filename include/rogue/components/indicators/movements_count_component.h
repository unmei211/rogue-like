#ifndef INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_

#include "lib/ecs/component.h"

class MovementsCountComponent : public IComponent {
 public:
  int count_ = 0;
  int aviable_steps_;
  explicit MovementsCountComponent(int aviable_steps = 100) : aviable_steps_(aviable_steps) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_
