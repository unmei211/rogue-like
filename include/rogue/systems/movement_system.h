#ifndef INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
class MovementSystem : public ISystem {
 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  std::string tag_ = "MovementSystem";
  void OnUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MOVEMENT_SYSTEM_H_
