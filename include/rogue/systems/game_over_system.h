#ifndef INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "lib/scenes/context.h"
#include "rogue/tools/entity_handler.h"
class GameOverSystem : public ISystem {
  EntityHandler* entity_handler_;
  Context* ctx_;
  void OnSystemUpdate(Entity* entity);
  void GameOver();

 protected:
  std::string tag_ = "GameOverSystem";
  void OnUpdate() override;

 public:
  GameOverSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* context,
                 EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_GAME_OVER_SYSTEM_H_
