#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_NAME_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_NAME_COMPONENT_H_

#include <string>

#include "lib/ecs/component.h"
class NameComponent : public IComponent {
 public:
  std::string name_;
  explicit NameComponent(const std::string& name = "") : name_(name) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_NAME_COMPONENT_H_
