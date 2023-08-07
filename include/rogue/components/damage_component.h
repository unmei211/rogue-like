#ifndef INCLUDE_ROGUE_COMPONENTS_DAMAGE_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_DAMAGE_COMPONENT_H_

#include "lib/ecs/component.h"
class DamageComponent : public IComponent {
 public:
  explicit DamageComponent(int damage = 10) : damage_(damage) {}
  int damage_;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_DAMAGE_COMPONENT_H_
