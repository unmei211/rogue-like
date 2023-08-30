#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_

#include <string>

#include "lib/ecs/entity.h"
#include "lib/ecs/system.h"
#include "rogue/tools/entity_map.h"
class TakeCoinSystem : public ISystem {
 private:
  void GiveCoins(Entity* entity);

 public:
  TakeCoinSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  std::string tag_ = "TakeCoinSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_COIN_SYSTEM_H_
