//
// Created by unmei on 7/22/23.
//

#include "rogue/scenes/game_scene.h"

#include <string>

#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/name_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/components/wallet_component.h"
#include "rogue/systems/collision_system.h"
#include "rogue/systems/entity_deletion_system.h"
#include "rogue/systems/hud_render_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/systems/movement_system.h"
#include "rogue/systems/rendering_system.h"
#include "rogue/systems/take_coin_system.h"
#include "rogue/systems/takes_system.h"

GameScene::GameScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameScene::OnCreate() {
  {
    auto coin = engine.GetEntityManager()->CreateEntity();
    coin->Add<TransformComponent>(Vec2(4, 3));
    coin->Add<TextureComponent>('$');
    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    coin->Add<TakeableComponent>();
    coin->Add<CostComponent>();
    coin->Add<RemovabilityComponent>();
    coin->Add<CoinComponent>();
  }

  {
    auto coin = engine.GetEntityManager()->CreateEntity();
    coin->Add<TransformComponent>(Vec2(5, 4));
    coin->Add<TextureComponent>('$');
    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    coin->Add<TakeableComponent>();
    coin->Add<CostComponent>();
    coin->Add<RemovabilityComponent>();
    coin->Add<CoinComponent>();
  }

  {
    auto player = engine.GetEntityManager()->CreateEntity();
    player->Add<TransformComponent>(Vec2(3, 3));
    player->Add<TextureComponent>('@');
    player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    player->Add<MovementComponent>(OnesVec2, ZeroVec2);
    player->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP);
    player->Add<LiftAbilityComponent>();
    player->Add<WalletComponent>();
    player->Add<MovementsCountComponent>();
  }

    {
      auto food = engine.GetEntityManager()->CreateEntity();
      // GameObject
      food->Add<TransformComponent>(Vec2(5, 6));
      food->Add<TextureComponent>('%');
      food->Add<ColliderComponent>(OnesVec2, ZeroVec2);
      // Takeable Object
      food->Add<TakeableComponent>();
      food->Add<RemovabilityComponent>();
      // FoodAttributes
      food->Add<NameComponent>("beef");
      food->Add<FoodComponent>();
    }

  auto sys_man = engine.GetSystemManager();

  sys_man->AddSystem<MoveControlSystem>(controls_);
  sys_man->AddSystem<MovementSystem>();
  sys_man->AddSystem<CollisionSystem>();
  sys_man->AddSystem<TakesSystem>();
  sys_man->AddSystem<TakeCoinSystem>();
  sys_man->AddSystem<EntityDeletionSystem>();
  sys_man->AddSystem<RenderingSystem>();
  sys_man->AddSystem<HudRenderSystem>();
}
void GameScene::OnRender() {
  engine.OnUpdate();
}

void GameScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
