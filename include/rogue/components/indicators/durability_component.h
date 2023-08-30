#ifndef INCLUDE_ROGUE_COMPONENTS_INDICATORS_DURABILITY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_INDICATORS_DURABILITY_COMPONENT_H_

#include "lib/ecs/component.h"
class DurabilityComponent : public IComponent {
 public:
  int multiplier_;
  int total_;
  int total_multiplied_;
  int current_;
  int current_multiplied_;

  void Subtract(int num) {
    current_multiplied_--;
    if (current_multiplied_ % (multiplier_) == 0) {
      current_--;
    }
  }
  explicit DurabilityComponent(int total, int multiplier, int current)
      : multiplier_(multiplier), total_(total), current_(current) {
    total_multiplied_ = total_ * multiplier_;
    current_multiplied_ = current_ * multiplier_;
  }
  explicit DurabilityComponent(int total = 1, int multiplier = 1) : multiplier_(multiplier), total_(total) {
    current_ = total_;
    total_multiplied_ = total_ * multiplier_;
    current_multiplied_ = current_ * multiplier_;
  }
};

#endif  // INCLUDE_ROGUE_COMPONENTS_INDICATORS_DURABILITY_COMPONENT_H_
