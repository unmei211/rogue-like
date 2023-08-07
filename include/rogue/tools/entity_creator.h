#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_

#include <BearLibTerminal.h>

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/math/vec2.h"
#include "rogue/components/action_component.h"
#include "rogue/components/breakable_component.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/damage_component.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/hp_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/name_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/components/stomach_component.h"
#include "rogue/components/tags/attack_tracker_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/door_component.h"
#include "rogue/components/tags/enemy_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/item_component.h"
#include "rogue/components/tags/loot_component.h"
#include "rogue/components/tags/manipulator_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/tags/target_component.h"
#include "rogue/components/tags/vision_component.h"
#include "rogue/components/tags/wall_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/components/wallet_component.h"
#include "rogue/tools/config/food_config.h"
#include "rogue/tools/data/player_food_data.h"

class EntityCreator {
  FoodConfig *food_config_;

  void AddFoodAttributes(Entity *entity, char texture, FoodData *food_data = nullptr) {
    int current;
    int multiplier;
    int total;
    if (food_data != nullptr) {
      texture = food_data->texture_;
      current = food_data->current_;
      multiplier = food_data->multiplier_;
      total = food_data->total_;
    } else {
      current = (*food_config_->GetName(texture)).length();
      multiplier = food_config_->GetNutritions(texture);
      total = current;
    }
    entity->Add<TextureComponent>(texture);
    entity->Add<NameComponent>(*food_config_->GetName(texture));
    entity->Add<DurabilityComponent>(total, multiplier, current);
    entity->Add<BreakableComponent>();
    entity->Add<FoodComponent>();
  }

 public:
  explicit EntityCreator(FoodConfig *const foodConfig) : food_config_(foodConfig) {}

  Entity *CreatePlayer(Entity *entity, char texture, Vec2 speed, int money, int steps_count, int aviable_steps,
                       int hp_current, int hp_max, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>(texture);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<MovementComponent>(speed, ZeroVec2);
    entity->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP, TK_Q, TK_E);
    entity->Add<LiftAbilityComponent>();
    entity->Add<TargetComponent>();
    {
      auto lac = entity->Get<LiftAbilityComponent>();
      lac->lifted_filter_.insert(typeid(CoinComponent));
      lac->lifted_filter_.insert(typeid(FoodComponent));
    }
    entity->Add<WalletComponent>(money);
    entity->Add<MovementsCountComponent>(aviable_steps, steps_count);
    entity->Add<StomachComponent>();
    entity->Add<Manipulator>();
    entity->Add<RigidBodyComponent>(false);
    entity->Add<HPComponent>(hp_current, hp_max);
    entity->Add<ActionComponent>();
    entity->Add<DamageComponent>();
    entity->Add<PlayerComponent>();
    return entity;
  }

  Entity *CreateEnemy(Entity *entity, char texture, Vec2 speed, int hp_current, int hp_max, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>(texture);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<MovementComponent>(speed, ZeroVec2);
    entity->Add<RigidBodyComponent>(true);
    entity->Add<VisionComponent>();
    entity->Add<AttackTrackerComponent>();
    entity->Add<HPComponent>(hp_current, hp_max);
    entity->Add<EnemyComponent>();
    entity->Add<DamageComponent>();
    return entity;
  }

  Entity *CreateCoin(Entity *entity, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('$');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<TakeableComponent>();
    entity->Add<CostComponent>();
    entity->Add<CoinComponent>();
    entity->Add<LootComponent>();
    return entity;
  }

  Entity *CreateWall(Entity *entity, Vec2 transform) {
    entity->Add<WallComponent>();
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('#');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<RigidBodyComponent>();
    return entity;
  }

  Entity *CreateFoodOnField(Entity *entity, Vec2 transform, char c) {
    AddFoodAttributes(entity, c);
    entity->Add<LootComponent>();
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<TakeableComponent>();
    return entity;
  }

  Entity *CreateFoodItem(Entity *entity, char c, FoodData *food_data = nullptr) {
    AddFoodAttributes(entity, c, food_data);
    entity->Add<ItemComponent>();
    return entity;
  }
  Entity *CreateDoor(Entity *entity, Vec2 transform, const std::string &level_name, char c) {
    entity->Add<TextureComponent>(c);
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<DoorComponent>(level_name);
    return entity;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
