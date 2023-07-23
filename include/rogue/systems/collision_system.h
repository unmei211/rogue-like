#ifndef INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"

class CollisionSystem : public ISystem {
 public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  std::string tag_ = "CollisionSystem";
  void OnUpdate() override;
  void OnPostUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_
