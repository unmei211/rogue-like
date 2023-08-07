#ifndef INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
#define INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
#include <map>
#include <string>
#include <vector>

#include "lib/ecs/engine.h"
#include "lib/scenes/context.h"
#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"
#include "rogue/tools/colliders_map.h"
#include "rogue/tools/data/player_food_data.h"
#include "rogue/tools/data/player_indicators_data.h"
class GameScene : public IScene {
  const Engine engine{};
  const Controls& controls_;
  LevelsManager levels_manager_;

  FoodConfig food_config_;
  LevelTransitionsConfig level_transitions_config_;

  SceneFiller scene_filler_;

  PlayerIndicatorsData player_indicators_data_;
  PlayerFoodData player_food_data_;

  EntityCreator entity_creator = EntityCreator(&food_config_);
 public:
  GameScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_GAME_SCENE_H_
