#include "rogue/scenes/game_scene.h"

#include <string>

#include "rogue/systems/game_over_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/tools/scene_filler.h"
GameScene::GameScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameScene::OnCreate() {
  player_indicators_data_ = PlayerIndicatorsData();
  player_food_data_ = PlayerFoodData();
  levels_manager_ = LevelsManager(&level_transitions_config_, engine.GetEntityManager(), engine.GetSystemManager());
  scene_filler_ = SceneFiller(&entity_creator, engine.GetEntityManager(), &food_config_, &player_indicators_data_,
                              &player_food_data_, &level_transitions_config_);
  levels_manager_.SetFiller(&scene_filler_);
  levels_manager_.SetLoadLevelName("level1");
}

void GameScene::OnRender() {
  if (levels_manager_.ChangeLevel()) {
    levels_manager_.LoadLevel(controls_, ctx_, &player_indicators_data_, &player_food_data_);
  }
  engine.OnUpdate();
}

void GameScene::OnExit() {
  StatsParser::WriteDown(
      "/home/unmei/Projects/Gardens/starovoytov.vladislav-game/include/rogue/tools/data/win_screen_stats",
      StatsParser::CastToVec(player_indicators_data_.steps_count_, player_indicators_data_.hp_current_,
                             player_indicators_data_.money_));
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
