#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLOR_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLOR_COMPONENT_H_

#include "lib/ecs/component.h"
#include "rogue/colors/colors.h"
class ColorComponent : public IComponent {
 public:
  explicit ColorComponent(Colors color = White) : color_(color) {}
  Colors color_;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_COLOR_COMPONENT_H_
