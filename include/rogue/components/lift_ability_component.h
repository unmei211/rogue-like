#ifndef INCLUDE_ROGUE_COMPONENTS_LIFT_ABILITY_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_LIFT_ABILITY_COMPONENT_H_

#include <set>

#include "lib/ecs/component.h"

class LiftAbilityComponent : public IComponent {
  std::set<Entity*> hand_picked_{};

 public:
  const std::set<Entity*>& GetHandPicked() const {
    return hand_picked_;
  }

  bool AnyPicked() const {
    return !hand_picked_.empty();
  }

  void PickUp(Entity* entity) {
    hand_picked_.insert(entity);
  }

  void Clear() {
    hand_picked_.clear();
  }
};

#endif  // INCLUDE_ROGUE_COMPONENTS_LIFT_ABILITY_COMPONENT_H_
