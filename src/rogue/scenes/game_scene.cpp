//
// Created by unmei on 7/22/23.
//

#include "rogue/scenes/game_scene.h"

#include "rogue/components/coin_component.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/components/wallet_component.h"
#include "rogue/systems/collision_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/systems/movement_system.h"
#include "rogue/systems/rendering_system.h"
#include "rogue/systems/take_coin_system.h"

GameScene::GameScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameScene::OnCreate() {
  {
    auto coin = engine.GetEntityManager()->CreateEntity();
    coin->Add<TransformComponent>(Vec2(10, 10));
    coin->Add<TextureComponent>('$');
    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    coin->Add<TakeableComponent>();
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
  }
  auto sm = engine.GetSystemManager();

  sm->AddSystem<MoveControlSystem>(controls_);
  sm->AddSystem<MovementSystem>();
  sm->AddSystem<CollisionSystem>();
  sm->AddSystem<TakeCoinSystem>();
  sm->AddSystem<RenderingSystem>();
}
void GameScene::OnRender() {
  engine.OnUpdate();
}

void GameScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
