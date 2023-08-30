#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_

#include <BearLibTerminal.h>

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/math/vec2.h"
#include "rogue/components/attributes/collider_component.h"
#include "rogue/components/attributes/color_component.h"
#include "rogue/components/attributes/medicine_slot_component.h"
#include "rogue/components/attributes/name_component.h"
#include "rogue/components/attributes/rigid_body_component.h"
#include "rogue/components/attributes/stomach_component.h"
#include "rogue/components/attributes/texture_component.h"
#include "rogue/components/attributes/transform_component.h"
#include "rogue/components/attributes/traps_slot_component.h"
#include "rogue/components/attributes/vision_component.h"
#include "rogue/components/attributes/wallet_component.h"
#include "rogue/components/capabilities/attack_tracker_component.h"
#include "rogue/components/capabilities/damage_component.h"
#include "rogue/components/capabilities/lift_ability_component.h"
#include "rogue/components/capabilities/movement_component.h"
#include "rogue/components/capabilities/player_control_component.h"
#include "rogue/components/indicators/cost_component.h"
#include "rogue/components/indicators/durability_component.h"
#include "rogue/components/indicators/floor_counter_component.h"
#include "rogue/components/indicators/hp_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/states/action_component.h"
#include "rogue/components/states/breakable_component.h"
#include "rogue/components/states/takeable_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/door_component.h"
#include "rogue/components/tags/enemy_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/item_component.h"
#include "rogue/components/tags/loot_component.h"
#include "rogue/components/tags/manipulator_component.h"
#include "rogue/components/tags/medicine_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/tags/target_component.h"
#include "rogue/components/tags/trap_component.h"
#include "rogue/components/tags/wall_component.h"
#include "rogue/tools/config/food_config.h"
#include "rogue/tools/config/graphics_associate.h"
#include "rogue/tools/data/player_food_data.h"

class EntityCreator {
  FoodConfig *food_config_;
  bool sprite = false;

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
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(*food_config_->GetColors(texture));
    }
    entity->Add<TextureComponent>(texture);
    entity->Add<NameComponent>(*food_config_->GetName(texture));
    entity->Add<DurabilityComponent>(total, multiplier, current);
    entity->Add<BreakableComponent>();
    entity->Add<FoodComponent>();
  }
  void AddMedicineAttributes(Entity *entity, char texture) {
    entity->Add<MedicineComponent>();
    entity->Add<TextureComponent>(texture);
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(GreenRedMedicine);
    }
  }

 public:
  explicit EntityCreator(FoodConfig *const foodConfig) : food_config_(foodConfig) {}
  void SetGraphicsAssociate(bool state) {
    sprite = state;
  }
  Entity *CreatePlayer(Entity *entity, char texture, Vec2 speed, int money, int steps_count, int aviable_steps,
                       int hp_current, int hp_max, Vec2 transform, char came_from, int traps_count, int floors_count) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>(texture);
    entity->Add<ColorComponent>(White);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<MovementComponent>(speed, ZeroVec2);
    entity->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP, TK_Q, TK_E, TK_R, TK_T);
    entity->Add<LiftAbilityComponent>();
    entity->Add<TargetComponent>();
    entity->Add<TrapsSlotComponent>(traps_count);
    {
      auto lac = entity->Get<LiftAbilityComponent>();
      lac->lifted_filter_.insert(typeid(CoinComponent));
      lac->lifted_filter_.insert(typeid(FoodComponent));
      lac->lifted_filter_.insert(typeid(MedicineComponent));
      lac->lifted_filter_.insert(typeid(TrapComponent));
    }
    entity->Add<WalletComponent>(money);
    entity->Add<MovementsCountComponent>(aviable_steps, steps_count);
    entity->Add<StomachComponent>();
    entity->Add<MedicineSlotComponent>();
    entity->Add<Manipulator>();
    entity->Add<FloorCounterComponent>(floors_count);
    entity->Add<RigidBodyComponent>(false);
    entity->Add<HPComponent>(hp_current, hp_max);
    entity->Add<ActionComponent>();
    entity->Get<ActionComponent>()->from_door_ = came_from;
    entity->Add<DamageComponent>();
    entity->Add<VisionComponent>(8);
    entity->Add<PlayerComponent>();
    return entity;
  }

  Entity *CreateEnemy(Entity *entity, char texture, Vec2 speed, int hp_current, int hp_max, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>(texture);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<MovementComponent>(speed, ZeroVec2);
    entity->Add<RigidBodyComponent>(true);
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(PinkEnemy);
    }
    entity->Add<VisionComponent>(6);
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
    entity->Add<ColorComponent>(YellowCoin);
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(YellowCoin);
    }
    entity->Add<CoinComponent>();
    entity->Add<LootComponent>();
    return entity;
  }

  Entity *CreateWall(Entity *entity, Vec2 transform) {
    entity->Add<WallComponent>();
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('#');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<ColorComponent>(WhiteWall);
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(WhiteWall);
    }
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

  Entity *CreateMedicineOnField(Entity *entity, Vec2 transform, char c) {
    AddMedicineAttributes(entity, c);
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2);
    entity->Add<LootComponent>();
    entity->Add<TakeableComponent>();
    return entity;
  }
  Entity *CreateMedicineItem(Entity *entity, char c) {
    AddMedicineAttributes(entity, c);
    entity->Add<ItemComponent>();
    return entity;
  }

  Entity *CreateFloorTrap(Entity *entity, char c, Vec2 transform) {
    entity->Add<TextureComponent>(c);
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2);
    entity->Add<ColorComponent>(WhiteFloorTrap);
    entity->Add<DamageComponent>(15);
    entity->Add<TrapComponent>();
    auto &st_as = entity->Get<TrapComponent>()->states_associates_;
    if (sprite) {
      st_as[0] = 0xE012;
      st_as[1] = 0xE013;
      st_as[2] = 0xE014;
    } else {
      st_as[0] = ',';
      st_as[1] = '*';
      st_as[2] = ';';
    }
    return entity;
  }

  Entity *CreateHandledTrap(Entity *entity, char c, Vec2 transform) {
    entity->Add<TextureComponent>(c);
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2);
    entity->Add<ColorComponent>(WhiteFloorTrap);
    entity->Add<DamageComponent>(25);
    entity->Add<TakeableComponent>();
    entity->Add<LootComponent>();
    entity->Add<TrapComponent>();

    auto &st_as = entity->Get<TrapComponent>()->states_associates_;
    if (sprite) {
      st_as[0] = 0xE015;
      st_as[1] = 0xE016;
      st_as[2] = 0xE017;
    } else {
      st_as[0] = 't';
      st_as[1] = 'u';
      st_as[2] = 'T';
    }
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
    entity->Add<ColorComponent>(BrownDoor);
    entity->Add<RigidBodyComponent>();
    entity->Get<RigidBodyComponent>()->is_rigid_ = true;
    if (sprite) {
      entity->Add<ColorComponent>(White);
    } else {
      entity->Add<ColorComponent>(BrownDoor);
    }
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<DoorComponent>(level_name);
    return entity;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
