#ifndef INCLUDE_ROGUE_COMPONENTS_REMOVABILITY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_REMOVABILITY_COMPONENT_H_

#include "lib/ecs/component.h"
class RemovabilityComponent : public IComponent {
 public:
  bool must_be_deleted_;
  explicit RemovabilityComponent(bool must_be_deleted = false) : must_be_deleted_(must_be_deleted) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_REMOVABILITY_COMPONENT_H_
