#ifndef INCLUDE_ROGUE_SYSTEMS_DAMAGE_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_DAMAGE_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
class DamageSystem : public ISystem {
  EntityHandler* entity_handler_;

 protected:
  std::string tag_ = "DamageSystem";
  void OnUpdate() override;

 public:
  DamageSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_DAMAGE_SYSTEM_H_
