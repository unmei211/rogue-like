#ifndef INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_

#include <constants.h>

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"

class PlayerIndicatorsSystem : public ISystem {
  EntityHandler* entity_handler_;
  const std::string& level_name_;
  void OnStepsUpdate(Entity* entity);

 protected:
  std::string tag_ = "PlayerIndicatorsSystem";
  void OnUpdate() override;

 public:
  PlayerIndicatorsSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                         const std::string& level_name);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_
