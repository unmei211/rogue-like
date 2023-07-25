#ifndef INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
#include <string>

#include "lib/ecs/system.h"
#include "lib/utils/controls.h"
class PlayerFoodSystem : public ISystem {
 protected:
  std::string tag_ = "PlayerFoodSystem";
  void OnUpdate() override;

 public:
  PlayerFoodSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
