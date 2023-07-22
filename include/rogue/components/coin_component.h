#ifndef INCLUDE_ROGUE_COMPONENTS_COIN_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_COIN_COMPONENT_H_

#include "lib/ecs/component.h"
class CoinComponent : public IComponent {
 public:
  unsigned int cost_;
  explicit CoinComponent(unsigned int cost = 5) : cost_(cost) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_COIN_COMPONENT_H_
