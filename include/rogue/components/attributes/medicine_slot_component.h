#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_MEDICINE_SLOT_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_MEDICINE_SLOT_COMPONENT_H_

#include "lib/ecs/component.h"
#include "rogue/tools/i_item_buffer.h"
class MedicineSlotComponent : public IComponent {
 public:
  int numbers_of_medicine_;
  explicit MedicineSlotComponent(int count = 0) : numbers_of_medicine_(count) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_MEDICINE_SLOT_COMPONENT_H_
