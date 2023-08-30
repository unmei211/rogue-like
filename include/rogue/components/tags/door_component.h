#ifndef INCLUDE_ROGUE_COMPONENTS_TAGS_DOOR_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_TAGS_DOOR_COMPONENT_H_

#include <string>
class DoorComponent : public IComponent {
 public:
  std::string level_name_;
  explicit DoorComponent(const std::string& level_name) : level_name_(level_name) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_TAGS_DOOR_COMPONENT_H_
