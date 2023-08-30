#ifndef INCLUDE_ROGUE_SYSTEMS_FLOOR_TRAPS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_FLOOR_TRAPS_SYSTEM_H_

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"
class FloorTrapsSystem : public ISystem {
  EntityMap* entity_map_;
  EntityHandler* entity_handler_;
  void OnTrapsUpdate();
  void CheckDamage();

 protected:
  void OnUpdate() override;

 public:
  FloorTrapsSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                   EntityMap* entity_map)
      : ISystem(entity_manager, system_manager), entity_map_(entity_map), entity_handler_(entity_handler) {}
};

#endif  // INCLUDE_ROGUE_SYSTEMS_FLOOR_TRAPS_SYSTEM_H_
