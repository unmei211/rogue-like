#ifndef INCLUDE_ROGUE_COMPONENTS_INDICATORS_FLOOR_COUNTER_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_INDICATORS_FLOOR_COUNTER_COMPONENT_H_

#include "lib/ecs/component.h"
class FloorCounterComponent : public IComponent {
 public:
  FloorCounterComponent() {}
  explicit FloorCounterComponent(int floors_count) : level_number(floors_count) {}
  int level_number = 1;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_INDICATORS_FLOOR_COUNTER_COMPONENT_H_
