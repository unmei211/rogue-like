#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_VISION_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_VISION_COMPONENT_H_
#include <vector>

#include "lib/ecs/component.h"
class VisionComponent : public IComponent {
 public:
  int distance_;

  explicit VisionComponent(int distance = 4) : distance_(distance) {}
};
#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_VISION_COMPONENT_H_
