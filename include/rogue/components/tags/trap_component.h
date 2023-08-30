#ifndef INCLUDE_ROGUE_COMPONENTS_TAGS_TRAP_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_TAGS_TRAP_COMPONENT_H_

#include <map>
#include <string>

#include "lib/ecs/component.h"
class TrapComponent : public IComponent {
 public:
  int current_state_ = 0;
  int steps_activity_ = 0;
  std::map<int, size_t> states_associates_;
  int GetState() {
    return current_state_;
  }
  void ToReady() {
    current_state_ = 1;
  }
  void ToForward() {
    current_state_ = 2;
  }

  void ToClose() {
    current_state_ = 0;
  }

  size_t GetAssociate() {
    return states_associates_[current_state_];
  }
};

#endif  // INCLUDE_ROGUE_COMPONENTS_TAGS_TRAP_COMPONENT_H_
