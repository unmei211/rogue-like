#include "rogue/scenes/game_scene.h"

#include <constants.h>

#include <string>

#include "rogue/systems/game_over_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/tools/scene_filler.h"
GameScene::GameScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameScene::OnCreate() {
  player_indicators_data_ = PlayerIndicatorsData();
  player_food_data_ = PlayerFoodData();
  levels_manager_ =
      LevelsManager(&level_transitions_config_, engine.GetEntityManager(), engine.GetSystemManager(), &entity_creator);
  scene_filler_ = SceneFiller(&entity_creator, engine.GetEntityManager(), &food_config_, &player_indicators_data_,
                              &player_food_data_, &level_transitions_config_);
  levels_manager_.SetFiller(&scene_filler_);
  std::ifstream fin;
  // levels_manager_.SetLoadLevelName(LEVEL_RANDOM_NAME);
  fin.open(RANDOM_MAP_TRIGGER_PATH);
  char c;
  if (fin.get(c)) {
    if (c == '1') {
      levels_manager_.SetLoadLevelName(LEVEL_RANDOM_NAME);
    } else {
      levels_manager_.SetLoadLevelName(LEVEL1_NAME);
    }
  } else {
    levels_manager_.SetLoadLevelName(LEVEL1_NAME);
  }
  fin.close();
  fin.open(GRAPHICS_SET_TRIGGER_PATH);
  if (fin.get(c)) {
    if (c == '1') {
      levels_manager_.graphics_associate_.Sprite();
      entity_creator.SetGraphicsAssociate(true);
    } else {
      entity_creator.SetGraphicsAssociate(false);
      levels_manager_.graphics_associate_.Default();
    }
  } else {
    entity_creator.SetGraphicsAssociate(false);
    levels_manager_.graphics_associate_.Default();
  }
  fin.close();
}

void GameScene::OnRender() {
  if (levels_manager_.ChangeLevel()) {
    levels_manager_.LoadLevel(controls_, ctx_, &player_indicators_data_, &player_food_data_);
  }
  engine.OnUpdate();
}

void GameScene::OnExit() {
  StatsParser::WriteDown(WIN_SCREEN_STATS_PATH,
                         StatsParser::CastToVec(player_indicators_data_.steps_count_,
                                                player_indicators_data_.hp_current_, player_indicators_data_.money_));
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
