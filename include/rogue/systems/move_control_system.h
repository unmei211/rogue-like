#ifndef INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_

#include "lib/utils/controls.h"
#include "lib/ecs/system.h"
class Entity;

class MoveControlSystem : public ISystem {
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  void OnUpdate() override;
 public:
  MoveControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_
