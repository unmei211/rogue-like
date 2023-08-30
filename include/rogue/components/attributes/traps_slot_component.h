#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TRAPS_SLOT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TRAPS_SLOT_COMPONENT_H_

#include "lib/ecs/component.h"
class TrapsSlotComponent : public IComponent {
 public:
  explicit TrapsSlotComponent(int traps_count = 0) : number_of_traps(traps_count) {}
  int number_of_traps = 0;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TRAPS_SLOT_COMPONENT_H_
