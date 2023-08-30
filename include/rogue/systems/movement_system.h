#ifndef INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_map.h"

class MovementSystem : public ISystem {
  EntityMap* const entity_map_;

 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityMap* entity_map);

 protected:
  std::string tag_ = "MovementSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
