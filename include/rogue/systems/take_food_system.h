#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
class Entity;

class TakeFoodSystem : public ISystem {
 public:
  TakeFoodSystem(EntityManager* entity_manager, SystemManager* system_manager);
  void GiveFood(Entity* entity);

 protected:
  std::string tag_ = "TakeFoodSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_
