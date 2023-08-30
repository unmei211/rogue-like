#ifndef INCLUDE_ROGUE_COMPONENTS_INDICATORS_HP_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_INDICATORS_HP_COMPONENT_H_

#include "lib/ecs/component.h"
class HPComponent : public IComponent {
 public:
  int heal_point_;
  int max_heal_point_;
  void AddHp(int value) {
    if (heal_point_ + value > max_heal_point_) {
      heal_point_ = max_heal_point_;
      return;
    }
    heal_point_ += value;
  }
  explicit HPComponent(int heal_point = 100, int max_heal_point = 100)
      : heal_point_(heal_point), max_heal_point_(max_heal_point) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_INDICATORS_HP_COMPONENT_H_
