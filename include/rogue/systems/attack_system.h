#ifndef INCLUDE_ROGUE_SYSTEMS_ATTACK_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ATTACK_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "lib/ecs/system_manager.h"
#include "rogue/tools/entity_handler.h"
class AttackSystem : public ISystem {
  EntityHandler* entity_handler_;

 protected:
  std::string tag_ = "AttackSystem";
  void OnUpdate() override;

 public:
  AttackSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ATTACK_SYSTEM_H_
