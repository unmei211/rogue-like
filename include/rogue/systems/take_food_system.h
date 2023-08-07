#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/colliders_map.h"
class Entity;

class TakeFoodSystem : public ISystem {
 private:
  void GiveFood(Entity* entity);
  CollidersMap* const colliders_map_;
 public:
  TakeFoodSystem(EntityManager* entity_manager, SystemManager* system_manager, CollidersMap* colliders_map);

 protected:
  std::string tag_ = "TakeFoodSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_FOOD_SYSTEM_H_
