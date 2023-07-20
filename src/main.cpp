#include <BearLibTerminal.h>

#include <string>

#include "game/CoinsManager.h"
#include "game/Controls.h"
#include "game/FoodManager.h"
#include "game/HoodRender.h"
#include "game/Player.h"
#include "lib/ecs/engine.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/systems/rendering_system.h"
int main() {
  terminal_open();

  terminal_refresh();
  // terminal_composition(TK_ON);
  Controls controls;
  const Engine engine{};
  {
    auto coin = engine.GetEntityManager()->CreateEntity();
    coin->Add<TransformComponent>(Vec2(16, 15));
    coin->Add<TextureComponent>('$');
    engine.GetSystemManager()->AddSystem<RenderingSystem>();
  }
  auto player = engine.GetEntityManager()->CreateEntity();
  player->Add<TransformComponent>(Vec2(15, 15));
  player->Add<TextureComponent>('@');
  player->Add<MovementComponent>();
  player->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP);
  engine.GetSystemManager()->AddSystem<RenderingSystem>();

  // CoinsManager coinsManager;
  // HoodRender hoodRender;
  // FoodManager foodManager;
  // Player player(5, 5, controls, coinsManager, foodManager);

  while (true) {
    terminal_clear();
    controls.Update();

    //    if (controls.IsExit() || player.GetFood()->GetSpent() == 0) {
    //      break;
    //    }

    if (controls.IsExit()) {
      break;
    }
    engine.OnUpdate();
    // coinsManager.Update(player.GetX(), player.GetY());
    // foodManager.Update(player.GetX(), player.GetY());
    // hoodRender.Render(player.GetMoneys(), player.GetSteps(), *player.GetFood());
    // player.Update();
    terminal_refresh();
  }

  terminal_close();
}
