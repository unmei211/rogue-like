#ifndef INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/colliders_map.h"
class Entity;

class RigidCollisionsSystem : public ISystem {
  CollidersMap* const colliders_map_;
  void OnRigidCollisions(Entity* entity);

 protected:
  std::string tag_ = "RigidCollisionsSystem";
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RigidCollisionsSystem(EntityManager* entity_manager, SystemManager* system_manager, CollidersMap* colliders_map);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_
