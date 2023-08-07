#ifndef INCLUDE_ROGUE_SYSTEMS_MARIONETTE_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_MARIONETTE_SYSTEM_H_
#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/colliders_map.h"
#include "rogue/tools/entity_handler.h"
class MarionetteSystem : public ISystem {
  CollidersMap* colliders_map_;
  EntityHandler* entity_handler_;
  void OnMarionetteUpdate(Entity* entity);

 protected:
  std::string tag_ = "MarionetteSystem";
  void OnUpdate() override;

 public:
  MarionetteSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                   CollidersMap* colliders_map);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_MARIONETTE_SYSTEM_H_
