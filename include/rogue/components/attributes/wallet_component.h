#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_WALLET_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_WALLET_COMPONENT_H_

#include "lib/ecs/component.h"
class WalletComponent : public IComponent {
 public:
  int moneys_;
  explicit WalletComponent(int moneys = 0) : moneys_(moneys) {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_WALLET_COMPONENT_H_
