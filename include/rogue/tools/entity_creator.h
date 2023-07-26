#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_

#include <BearLibTerminal.h>

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/math/vec2.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/indicators/movements_count_component.h"
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
class EntityCreator {
 private:
  void CreatePlayer(Entity* player, Vec2 transform) {
    player->Add<TransformComponent>(transform);
    player->Add<TextureComponent>('@');
    player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    player->Add<MovementComponent>(OnesVec2, ZeroVec2);
    player->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP, TK_Q);
    player->Add<LiftAbilityComponent>();
    player->Add<WalletComponent>();
    player->Add<MovementsCountComponent>();
    player->Add<PlayerComponent>();
    player->Add<StomachComponent>();
    player->Add<RigidBodyComponent>(false);
  }
  void CreateCoin(Entity* coin, Vec2 transform) {
    coin->Add<TransformComponent>(transform);
    coin->Add<TextureComponent>('$');
    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    coin->Add<TakeableComponent>();
    coin->Add<CostComponent>();
    coin->Add<CoinComponent>();
    coin->Add<LootComponent>();
  }
  void CreateWall(Entity* wall, Vec2 transform) {
    wall->Add<WallComponent>();
    wall->Add<TransformComponent>(transform);
    wall->Add<TextureComponent>('#');
    wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    wall->Add<RigidBodyComponent>();
  }
  void CreateFood(Entity* food, Vec2 transform, std::string name) {
    food->Add<LootComponent>();
    food->Add<TransformComponent>(transform);
    food->Add<TextureComponent>('%');
    food->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    food->Add<TakeableComponent>();
    food->Add<NameComponent>(name);
    food->Add<FoodComponent>();
  }

 public:
  Entity* CreateEntity(Entity* entity, std::type_index tag, Vec2 transfrom) {
    if (tag == typeid(PlayerComponent)) {
      CreatePlayer(entity, transfrom);
    } else if (tag == typeid(CoinComponent)) {
      CreateCoin(entity, transfrom);
    } else if (tag == typeid(WallComponent)) {
      CreateWall(entity, transfrom);
    }
    return entity;
  }
  Entity* CreateEntity(Entity* entity, std::type_index tag, Vec2 transfrom, std::string name) {
    if (tag == typeid(FoodComponent)) {
      CreateFood(entity, transfrom, name);
    }
    return entity;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_CREATOR_H_
