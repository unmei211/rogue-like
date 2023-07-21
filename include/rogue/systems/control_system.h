#ifndef INCLUDE_ROGUE_SYSTEMS_CONTROL_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_CONTROL_SYSTEM_H_

#include "game/Controls.h"
#include "lib/ecs/system.h"
class Entity;

class ControlSystem : public ISystem {
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  void OnUpdate() override;
 public:
  ControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_CONTROL_SYSTEM_H_
