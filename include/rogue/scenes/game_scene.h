#ifndef INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
#define INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
#include <string>
#include <vector>

#include "lib/ecs/engine.h"
#include "lib/scenes/context.h"
#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"

class GameScene : public IScene {
  const Engine engine{};
  //  Engine* engine;
  const Controls& controls_;
  const std::string first_map_path = "/home/unmei/Projects/Other/rogue-like/include/rogue/maps/first_map";
  std::vector<std::vector<char>> game_map_;
  EntityCreator entity_creator_;

 public:
  GameScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
