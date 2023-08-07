#ifndef INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system.h"
#include "lib/utils/controls.h"
#include "rogue/tools/colliders_map.h"
#include "rogue/tools/entity_handler.h"
class AbilityControlSystem : public ISystem {
 private:
  EntityHandler* entity_handler_;
  CollidersMap* colliders_map_;
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity);
  void CreateMarionette(Entity* entity, const Vec2& cage_pos);

 protected:
  std::string tag_ = "AbilityControlSystem";
  void OnUpdate() override;

 public:
  AbilityControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                       EntityHandler* entity_handler, CollidersMap* colliders_map);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ABILITY_CONTROL_SYSTEM_H_
