#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_

#include <BearLibTerminal.h>

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/math/vec2.h"
#include "rogue/components/breakable_component.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/item_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/name_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/components/stomach_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/loot_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/tags/wall_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/components/wallet_component.h"
#include "rogue/tools/config/food_config.h"
class EntityCreator {
  FoodConfig* foodConfig_;
  void AddFoodAttributes(Entity* entity, char c) {
    entity->Add<TextureComponent>(c);
    entity->Add<NameComponent>(*foodConfig_->GetName(c));
    std::cout << (*foodConfig_->GetName(c)).length();
    entity->Add<DurabilityComponent>((*foodConfig_->GetName(c)).length(), foodConfig_->GetNutritions(c));
    entity->Add<BreakableComponent>();
    entity->Add<FoodComponent>();
  }

 public:
  explicit EntityCreator(FoodConfig* const foodConfig) : foodConfig_(foodConfig) {}
  Entity* CreatePlayer(Entity* entity, Entity* food1, Entity* food2, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('@');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<MovementComponent>(OnesVec2, ZeroVec2);
    entity->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP, TK_Q);
    entity->Add<LiftAbilityComponent>();
    entity->Add<WalletComponent>();
    entity->Add<MovementsCountComponent>();
    entity->Add<PlayerComponent>();
    entity->Add<StomachComponent>();
    entity->Get<StomachComponent>()->AddFood(food1);
    entity->Get<StomachComponent>()->AddFood(food2);
    entity->Add<RigidBodyComponent>(false);
    return entity;
  }
  Entity* CreateCoin(Entity* entity, Vec2 transform) {
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('$');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<TakeableComponent>();
    entity->Add<CostComponent>();
    entity->Add<CoinComponent>();
    entity->Add<LootComponent>();
    return entity;
  }
  Entity* CreateWall(Entity* entity, Vec2 transform) {
    entity->Add<WallComponent>();
    entity->Add<TransformComponent>(transform);
    entity->Add<TextureComponent>('#');
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<RigidBodyComponent>();
    return entity;
  }
  Entity* CreateFoodOnField(Entity* entity, Vec2 transform, char c) {
    AddFoodAttributes(entity, c);
    entity->Add<LootComponent>();
    entity->Add<TransformComponent>(transform);
    entity->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    entity->Add<TakeableComponent>();
    return entity;
  }
  Entity* CreateFoodItem(Entity* entity, char c) {
    AddFoodAttributes(entity, c);
    entity->Add<ItemComponent>();
    return entity;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
