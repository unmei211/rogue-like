#ifndef INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_

#include "lib/ecs/system.h"
class PlayerIndicatorsSystem : public ISystem {
  void OnStepsUpdate(Entity* entity);

 protected:
  void OnUpdate() override;

 public:
  PlayerIndicatorsSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_PLAYER_INDICATORS_SYSTEM_H_
