#ifndef INCLUDE_ROGUE_SYSTEMS_PLAYER_RIGID_COLLISIONS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_PLAYER_RIGID_COLLISIONS_SYSTEM_H_

#include "lib/ecs/system.h"

class Entity;

class PlayerRigidCollisionsSystem : public ISystem {
  void OnRigidCollisions(Entity* entity);

 protected:
  void OnUpdate() override;

 public:
  PlayerRigidCollisionsSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_PLAYER_RIGID_COLLISIONS_SYSTEM_H_
