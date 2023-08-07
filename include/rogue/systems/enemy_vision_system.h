#ifndef INCLUDE_ROGUE_SYSTEMS_ENEMY_VISION_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_ENEMY_VISION_SYSTEM_H_
#include <string>
#include <utility>
#include "lib/ecs/system_manager.h"
#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
class EnemyVisionSystem : public ISystem {
  EntityHandler* entity_handler_;

 protected:
  std::string tag_ = "EnemyVisionSystem";
  void OnUpdate() override;

 public:
  EnemyVisionSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_ENEMY_VISION_SYSTEM_H_
