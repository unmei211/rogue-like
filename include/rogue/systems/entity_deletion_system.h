#ifndef INCLUDE_ROGUE_SYSTEMS_ENTITY_DELETION_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ENTITY_DELETION_SYSTEM_H_
#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_map.h"
class EntityDeletionSystem : public ISystem {
  EntityMap* const entity_map_;

 public:
  EntityDeletionSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                       EntityMap* const entity_map);

 protected:
  std::string tag_ = "EntityDeletionSystem";
  void OnPostUpdate() override;
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ENTITY_DELETION_SYSTEM_H_
