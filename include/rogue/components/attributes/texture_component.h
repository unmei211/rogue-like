#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TEXTURE_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TEXTURE_COMPONENT_H_

#include "lib/ecs/component.h"

class TextureComponent : public IComponent {
 public:
  char symbol_;
  explicit TextureComponent(char symbol) : symbol_(symbol) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_TEXTURE_COMPONENT_H_
