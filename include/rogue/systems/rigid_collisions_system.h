#ifndef INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_map.h"
class Entity;

class RigidCollisionsSystem : public ISystem {
  EntityMap* const entity_map_;
  void OnRigidCollisions(Entity* entity);

 protected:
  std::string tag_ = "RigidCollisionsSystem";
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RigidCollisionsSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityMap* entity_map);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_RIGID_COLLISIONS_SYSTEM_H_
