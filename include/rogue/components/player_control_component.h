#ifndef INCLUDE_ROGUE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_

#include "lib/ecs/component.h"

class PlayerControlComponent : public IComponent {
 public:
  int right_button_;
  int left_button_;
  int down_button_;
  int up_button_;

  PlayerControlComponent(int right_button, int left_button, int down_button, int up_button)
      : right_button_(right_button), left_button_(left_button), down_button_(down_button), up_button_(up_button) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
