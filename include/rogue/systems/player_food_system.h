#ifndef INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
#include <string>

#include "lib/ecs/system.h"
#include "lib/utils/controls.h"
#include "rogue/tools/entity_handler.h"
class PlayerFoodSystem : public ISystem {
  EntityHandler* entity_handler_;
 protected:
  std::string tag_ = "PlayerFoodSystem";
  void OnUpdate() override;
  void OnPlayerFoodUpdate(Entity* entity);
 public:
  PlayerFoodSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_PLAYER_FOOD_SYSTEM_H_
