#include <BearLibTerminal.h>

#include "lib/ecs/engine.h"
#include "lib/utils/controls.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/systems/move_control_system.h"
#include "rogue/systems/movement_system.h"
#include "rogue/systems/rendering_system.h"

int main() {
  terminal_open();
  terminal_refresh();

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
  player->Add<MovementComponent>(Vec2(1, 1), ZeroVec2);
  player->Add<PlayerControlComponent>(TK_RIGHT, TK_LEFT, TK_DOWN, TK_UP);
  engine.GetSystemManager()->AddSystem<MoveControlSystem>(controls);
  engine.GetSystemManager()->AddSystem<MovementSystem>();
  engine.GetSystemManager()->AddSystem<RenderingSystem>();

  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE) || controls.IsPressed(TK_ESCAPE)) {
      break;
    }
    engine.OnUpdate();
    controls.Reset();
    terminal_refresh();
  }

  terminal_close();
}
