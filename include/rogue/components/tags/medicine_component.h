#ifndef INCLUDE_ROGUE_COMPONENTS_TAGS_MEDICINE_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_TAGS_MEDICINE_COMPONENT_H_

#include "lib/ecs/component.h"
class MedicineComponent : public IComponent {
 public:
  explicit MedicineComponent(int treatment_value = 25) : treatment_value_(treatment_value) {}
  int treatment_value_;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_TAGS_MEDICINE_COMPONENT_H_
