#ifndef INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_ATTACK_TRACKER_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_ATTACK_TRACKER_COMPONENT_H_

#include "lib/ecs/component.h"
#include "lib/ecs/entity.h"
class AttackTrackerComponent : public IComponent {
 public:
  explicit AttackTrackerComponent(Entity* attack_him = nullptr) : attack_him_(attack_him) {}
  Entity* attack_him_;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_CAPABILITIES_ATTACK_TRACKER_COMPONENT_H_
