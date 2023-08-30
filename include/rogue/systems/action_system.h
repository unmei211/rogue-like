#ifndef INCLUDE_ROGUE_SYSTEMS_ACTION_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ACTION_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
class ActionSystem : public ISystem {
  EntityHandler* entity_handler_;

 protected:
  std::string tag_ = "ActionSystem";
  void OnPreUpdate() override;

 public:
  ActionSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ACTION_SYSTEM_H_
