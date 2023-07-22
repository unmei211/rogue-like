#ifndef INCLUDE_ROGUE_COMPONENTS_WALLET_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_WALLET_COMPONENT_H_

#include "lib/ecs/component.h"
class WalletComponent : public IComponent {
 public:
  unsigned int moneys_;
  explicit WalletComponent(unsigned int moneys = 0) : moneys_(moneys) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_WALLET_COMPONENT_H_