#ifndef INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_

#include "lib/ecs/component.h"
static const int aviable_steps_default_ = 100;
class MovementsCountComponent : public IComponent {
 public:
  int count_;
  int aviable_steps_;
  explicit MovementsCountComponent(int aviable_steps = aviable_steps_default_, int count = 0)
      : count_(count), aviable_steps_(aviable_steps) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_INDICATORS_MOVEMENTS_COUNT_COMPONENT_H_
