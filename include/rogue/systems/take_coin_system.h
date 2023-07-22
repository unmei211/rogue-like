#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_

#include "lib/ecs/system.h"
class TakeCoinSystem : public ISystem {
 public:
  TakeCoinSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_
