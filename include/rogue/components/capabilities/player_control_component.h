#ifndef INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_PLAYER_CONTROL_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_PLAYER_CONTROL_COMPONENT_H_

#include "lib/ecs/component.h"

class PlayerControlComponent : public IComponent {
 public:
  int right_button_;
  int left_button_;
  int down_button_;
  int up_button_;
  int switch_food_button_;    // 'Q'
  int walk_for_food_button_;  // 'E'
  int use_heal_button_;       // 'R'
  int throw_trap_button_;     // 'T'

  PlayerControlComponent(int right_button, int left_button, int down_button, int up_button, int switch_food_button,
                         int walk_for_food_button, int use_heal_button, int throw_trap_button)
      : right_button_(right_button),
        left_button_(left_button),
        down_button_(down_button),
        up_button_(up_button),
        switch_food_button_(switch_food_button),
        walk_for_food_button_(walk_for_food_button),
        use_heal_button_(use_heal_button),
        throw_trap_button_(throw_trap_button) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_PLAYER_CONTROL_COMPONENT_H_
