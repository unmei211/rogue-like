#ifndef INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#define INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#include <string>
#include <vector>

#include "rogue/tools/data/player_food_data.h"

class SceneFiller {
  EntityCreator* entity_creator_;
  EntityManager* entity_manager_;
  LevelTransitionsConfig* level_transitions_config_;
  FoodConfig* food_config_;
  PlayerIndicatorsData* player_indicators_data_;
  PlayerFoodData* player_food_data_;
  size_t player_id_ = 0;

 public:
  SceneFiller() = default;
  ~SceneFiller() = default;
  SceneFiller(EntityCreator* entity_creator, EntityManager* entity_manager, FoodConfig* food_config,
              PlayerIndicatorsData* player_indicators_data, PlayerFoodData* player_food_data,
              LevelTransitionsConfig* level_transitions_config)
      : entity_creator_(entity_creator),
        entity_manager_(entity_manager),
        level_transitions_config_(level_transitions_config),
        food_config_(food_config),
        player_indicators_data_(player_indicators_data),
        player_food_data_(player_food_data) {}

  size_t GetPlayerID() {
    return player_id_;
  }
  void Fill(CollidersMap* colliders_map, std::vector<std::vector<char>>* map_, const std::string& current_name_) {
    auto temp_map = *map_;
    for (int i = 0; i < static_cast<int>(temp_map.size()); i++) {
      for (int j = 0; j < static_cast<int>(temp_map[0].size()); j++) {
        char c = temp_map[i][j];
        if (c == '#') {
          colliders_map->Put(Vec2(j, i), entity_creator_->CreateWall(entity_manager_->CreateEntity(), Vec2(j, i)));
        } else if (c == '$') {
          colliders_map->Put(Vec2(j, i), entity_creator_->CreateCoin(entity_manager_->CreateEntity(), Vec2(j, i)));
        } else if (c == '@') {
          auto player = entity_creator_->CreatePlayer(
              entity_manager_->CreateEntity(), player_indicators_data_->texture_, player_indicators_data_->speed_,
              player_indicators_data_->money_, player_indicators_data_->steps_count_,
              player_indicators_data_->aviable_steps_, player_indicators_data_->hp_current_,
              player_indicators_data_->hp_max_, Vec2(j, i));
          player_id_ = player->GetId();
          for (auto& food_data : *player_food_data_->GetFoodData()) {
            auto food = entity_creator_->CreateFoodItem(entity_manager_->CreateEntity(), c, &food_data);
            player->Get<StomachComponent>()->AddFood(food);
          }
          colliders_map->Put(Vec2(j, i), player);
        } else if (food_config_->Contains(c)) {
          colliders_map->Put(Vec2(j, i),
                             entity_creator_->CreateFoodOnField(entity_manager_->CreateEntity(), Vec2(j, i), c));
        } else if (c == '<') {
          colliders_map->Put(Vec2(j, i),
                             entity_creator_->CreateDoor(entity_manager_->CreateEntity(), Vec2(j, i),
                                                         *level_transitions_config_->GetPrevious(current_name_), c));
        } else if (c == '>') {
          colliders_map->Put(
              Vec2(j, i), entity_creator_->CreateDoor(entity_manager_->CreateEntity(), Vec2(j, i),
                                                      *level_transitions_config_->GetNextLevelName(current_name_), c));
        } else if (c == 'E') {
          colliders_map->Put(Vec2(j, i), entity_creator_->CreateEnemy(entity_manager_->CreateEntity(), c, OnesVec2, 40,
                                                                      40, Vec2(j, i)));
        }
      }
    }
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
