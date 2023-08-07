#ifndef INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_

#include <list>
#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/colliders_map.h"

class CollisionSystem : public ISystem {
  CollidersMap* const colliders_map_;

 public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager, CollidersMap* const colliders_map);

 protected:
  std::string tag_ = "CollisionSystem";
  void OnUpdate() override;
  void OnPostUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_COLLISION_SYSTEM_H_
