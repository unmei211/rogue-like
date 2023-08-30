#ifndef INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "lib/utils/controls.h"
#include "rogue/tools/entity_handler.h"

class Entity;

class MoveControlSystem : public ISystem {
  const Controls& controls_;
  EntityHandler* entity_handler_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  std::string tag_ = "MoveControlSystem";
  void OnUpdate() override;

 public:
  MoveControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                    EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MOVE_CONTROL_SYSTEM_H_
