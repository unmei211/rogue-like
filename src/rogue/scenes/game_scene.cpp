#include "rogue/scenes/game_scene.h"

#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/item_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/name_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
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
#include "rogue/systems/ability_control_system.h"
#include "rogue/systems/collision_system.h"
#include "rogue/systems/entity_deletion_system.h"
#include "rogue/systems/game_over_system.h"
#include "rogue/systems/hud_render_system.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/systems/movement_system.h"
#include "rogue/systems/player_food_system.h"
#include "rogue/systems/player_indicators_system.h"
#include "rogue/systems/player_rigid_collisions_system.h"
#include "rogue/systems/rendering_system.h"
#include "rogue/systems/take_coin_system.h"
#include "rogue/systems/take_food_system.h"
#include "rogue/systems/takes_system.h"
#include "rogue/tools/scene_filler.h"

GameScene::GameScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameScene::OnCreate() {
  // engine = new Engine;
  terminal_composition(TK_ON);
  SceneFiller scene_filler(engine.GetMapReader());
  scene_filler.InitMap(&first_map_path);
  game_map_ = scene_filler.GetMap();
  scene_filler.Fill(engine.GetEntityManager(), &entity_creator_);
  //  {
  //    auto player = engine.GetEntityManager()->CreateEntity();
  //    player->Add<TransformComponent>(Vec2(5, 5));
  //    player->Add<TextureComponent>('@');
  //    player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //    player->Add<MovementComponent>(OnesVec2, ZeroVec2);
  //    player->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP, TK_Q);
  //    player->Add<LiftAbilityComponent>();
  //    player->Add<WalletComponent>();
  //    player->Add<MovementsCountComponent>(10);
  //    player->Add<PlayerComponent>();
  //    player->Add<StomachComponent>();
  //    player->Add<RigidBodyComponent>(false);
  //  }
  //
  //  {
  //    auto coin = engine.GetEntityManager()->CreateEntity();
  //    coin->Add<TransformComponent>(Vec2(5, 6));
  //    coin->Add<TextureComponent>('$');
  //    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //    coin->Add<TakeableComponent>();
  //    coin->Add<CostComponent>();
  //    coin->Add<CoinComponent>();
  //    coin->Add<LootComponent>();
  //  }

  auto sys_man = engine.GetSystemManager();

  sys_man->AddSystem<MoveControlSystem>(controls_);
  sys_man->AddSystem<AbilityControlSystem>(controls_);
  sys_man->AddSystem<MovementSystem>();
  sys_man->AddSystem<CollisionSystem>();
  sys_man->AddSystem<PlayerRigidCollisionsSystem>();
  sys_man->AddSystem<TakesSystem>();
  sys_man->AddSystem<TakeCoinSystem>();
  sys_man->AddSystem<PlayerFoodSystem>();
  sys_man->AddSystem<TakeFoodSystem>();
  sys_man->AddSystem<PlayerIndicatorsSystem>();
  sys_man->AddSystem<GameOverSystem>(ctx_);
  sys_man->AddSystem<EntityDeletionSystem>();
  sys_man->AddSystem<HudRenderSystem>();
  sys_man->AddSystem<RenderingSystem>();
}
void GameScene::OnRender() {
  engine.OnUpdate();
}

void GameScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
  // delete engine;
  std::cout << "Удаляй" << std::endl;
}
