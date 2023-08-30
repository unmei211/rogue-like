#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_TRAP_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_TRAP_SYSTEM_H_

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"
class TakeTrapSystem : public ISystem {
  EntityHandler* entity_handler_;
  EntityMap* entity_map_;
  void OnTakeTrap(Entity* player);

 protected:
  void OnUpdate() override;

 public:
  TakeTrapSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                 EntityMap* entity_map)
      : ISystem(entity_manager, system_manager), entity_handler_(entity_handler), entity_map_(entity_map) {}
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_TRAP_SYSTEM_H_
