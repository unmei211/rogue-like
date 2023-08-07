#ifndef INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/colliders_map.h"

class MovementSystem : public ISystem {
  CollidersMap* const colliders_map_;

 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager, CollidersMap* colliders_map);

 protected:
  std::string tag_ = "MovementSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
