#ifndef INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
#define INCLUDE_ROGUE_SCENES_GAME_SCENE_H_

#include "lib/ecs/engine.h"
#include "lib/scenes/context.h"
#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"

class GameScene : public IScene{
  const Engine engine;
  const Controls& controls_;

 public:
  GameScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
