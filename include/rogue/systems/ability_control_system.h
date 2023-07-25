#ifndef INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system.h"
#include "lib/utils/controls.h"
class AbilityControlSystem : public ISystem {
 private:
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  std::string tag_ = "AbilityControlSystem";
  void OnUpdate() override;

 public:
  AbilityControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
