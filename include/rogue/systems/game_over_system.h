#ifndef INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_

#include "lib/ecs/system.h"
#include "lib/scenes/context.h"
class GameOverSystem : public ISystem {
  Context* ctx_;
  void OnSystemUpdate(Entity* entity);
  void GameOver();

 protected:
  void OnUpdate() override;

 public:
  GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* context);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_
