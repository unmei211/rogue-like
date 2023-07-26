#include <BearLibTerminal.h>

#include "lib/scenes/context.h"
#include "lib/scenes/scene_manager.h"
#include "lib/utils/controls.h"
#include "rogue/scenes/game_over_scene.h"
#include "rogue/scenes/game_scene.h"
#include "rogue/scenes/title_scene.h"

int main() {
  terminal_open();
  terminal_set("window: title='luvSashuLul'");
  terminal_refresh();

  Controls controls;

  Context ctx{};
  SceneManager sm(ctx);

  sm.Put("title", new TitleScene(&ctx, controls));
  sm.Put("game", new GameScene(&ctx, controls));
  sm.Put("game_over", new GameOverScene(&ctx, controls));

  ctx.scene_ = "title";
  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE) || controls.IsPressed(TK_ESCAPE)) {
      break;
    }

    sm.OnRender();
    controls.Reset();
    // terminal_refresh();
  }
  sm.OnExit();
  terminal_close();
}
