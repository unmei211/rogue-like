#ifndef INCLUDE_ROGUE_TOOLS_LEVELS_MANAGER_H_
#define INCLUDE_ROGUE_TOOLS_LEVELS_MANAGER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "lib/ecs/system_manager.h"
#include "lib/scenes/context.h"
#include "rogue/systems/ability_control_system.h"
#include "rogue/systems/action_system.h"
#include "rogue/systems/attack_system.h"
#include "rogue/systems/collision_system.h"
#include "rogue/systems/damage_system.h"
#include "rogue/systems/enemy_vision_system.h"
#include "rogue/systems/entity_deletion_system.h"
#include "rogue/systems/game_over_system.h"
#include "rogue/systems/hud_render_system.h"
#include "rogue/systems/level_transition_system.h"
#include "rogue/systems/marionette_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/systems/movement_system.h"
#include "rogue/systems/player_food_system.h"
#include "rogue/systems/player_indicators_system.h"
#include "rogue/systems/rendering_system.h"
#include "rogue/systems/rigid_collisions_system.h"
#include "rogue/systems/take_coin_system.h"
#include "rogue/systems/take_food_system.h"
#include "rogue/systems/takes_system.h"
#include "rogue/systems/targeting_system.h"
#include "rogue/tools/colliders_map.h"
#include "rogue/tools/config/level_transitions_config.h"
#include "rogue/tools/data/player_food_data.h"
#include "rogue/tools/data/player_indicators_data.h"
#include "rogue/tools/map_reader.h"
#include "rogue/tools/scene_filler.h"
#include "rogue/tools/stats_parser.h"

class LevelsManager {
 private:
  std::map<std::string, std::string> levels_path_;
  LevelTransitionsConfig* level_transitions_config_;
  SceneFiller* scene_filler_;
  std::vector<std::vector<char>> game_map_;
  CollidersMap colliders_map_;
  EntityManager* entity_manager_;
  SystemManager* system_manager_;
  MapReader map_reader = MapReader(25, 80);

  EntityHandler entity_handler_;

 public:
  LevelsManager() = default;
  explicit LevelsManager(LevelTransitionsConfig* level_transitions_config, EntityManager* entity_manager,
                         SystemManager* system_manager)
      : level_transitions_config_(level_transitions_config),
        colliders_map_(CollidersMap(0, 0)),
        entity_manager_(entity_manager),
        system_manager_(system_manager),
        entity_handler_(EntityHandler(entity_manager)) {
    levels_path_["level1"] = "/home/unmei/Projects/Gardens/starovoytov.vladislav-game/include/rogue/maps/level1";
    levels_path_["level2"] = "/home/unmei/Projects/Gardens/starovoytov.vladislav-game/include/rogue/maps/level2";
  }
  std::string current_level_name_ = "";
  std::string load_level_name_ = "";
  LevelTransitionsConfig* GetLevelTransitionsConfig() {
    return level_transitions_config_;
  }
  void SetFiller(SceneFiller* scene_filler) {
    scene_filler_ = scene_filler;
  }

  std::string* GetPath(std::string* level_name) {
    if (levels_path_.count(*level_name) == 0) {
      return nullptr;
    }
    return &levels_path_[*level_name];
  }
  void LoadLevel(const Controls& controls, Context* ctx, PlayerIndicatorsData* player_indicators_data,
                 PlayerFoodData* player_food_data) {
    {
      auto player = entity_manager_->Get(scene_filler_->GetPlayerID());
      if (player != nullptr) {
        player_indicators_data->SetData(player);
        // git player_indicators_data->from_level_ = load_level_name_;
        player_food_data->SetData(player->Get<StomachComponent>()->GetFoodQueue());
      }
    }
    entity_manager_->DeleteAll();
    system_manager_->DeleteAll();

    colliders_map_.Clear();
    if (load_level_name_ == "title" || load_level_name_ == "win") {
      ctx->scene_ = load_level_name_;
      return;
    }
    current_level_name_ = load_level_name_;
    map_reader.ReadPath(&levels_path_[current_level_name_]);
    game_map_ = map_reader.Get();
    colliders_map_ = CollidersMap(game_map_.size(), game_map_[0].size());

    scene_filler_->Fill(&colliders_map_, &game_map_, current_level_name_);

    entity_handler_.Update();
    system_manager_->AddSystem<ActionSystem>(&entity_handler_);
    system_manager_->AddSystem<MoveControlSystem>(controls, &entity_handler_);
    system_manager_->AddSystem<AbilityControlSystem>(controls, &entity_handler_, &colliders_map_);
    system_manager_->AddSystem<AttackSystem>(&entity_handler_);
    system_manager_->AddSystem<MovementSystem>(&colliders_map_);
    system_manager_->AddSystem<CollisionSystem>(&colliders_map_);
    system_manager_->AddSystem<RigidCollisionsSystem>(&colliders_map_);
    system_manager_->AddSystem<EnemyVisionSystem>(&entity_handler_);
    system_manager_->AddSystem<TargetingSystem>(&colliders_map_, &entity_handler_);
    system_manager_->AddSystem<DamageSystem>(&entity_handler_);
    system_manager_->Disable<DamageSystem>();
    system_manager_->Disable<TargetingSystem>();
    system_manager_->AddSystem<TakesSystem>();
    system_manager_->AddSystem<TakeCoinSystem>();
    system_manager_->AddSystem<MarionetteSystem>(&entity_handler_, &colliders_map_);
    system_manager_->Disable<MarionetteSystem>();
    system_manager_->AddSystem<PlayerFoodSystem>(&entity_handler_);
    system_manager_->AddSystem<TakeFoodSystem>(&colliders_map_);
    system_manager_->AddSystem<PlayerIndicatorsSystem>(&entity_handler_);
    system_manager_->AddSystem<GameOverSystem>(ctx, &entity_handler_);
    system_manager_->AddSystem<LevelTransitionSystem>(&this->load_level_name_, &entity_handler_);
    system_manager_->AddSystem<EntityDeletionSystem>(&colliders_map_);
    system_manager_->AddSystem<HudRenderSystem>(&entity_handler_);
    system_manager_->AddSystem<RenderingSystem>();
  }
  void SetLoadLevelName(const std::string& load_level_name) {
    load_level_name_ = load_level_name;
  }
  std::string* GetCurrentName() {
    return &current_level_name_;
  }
  bool ChangeLevel() {
    return current_level_name_ != load_level_name_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_LEVELS_MANAGER_H_
