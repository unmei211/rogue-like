#include <BearLibTerminal.h>
#include <constants.h>

#include "lib/scenes/context.h"
#include "lib/scenes/scene_manager.h"
#include "lib/utils/controls.h"
#include "rogue/colors/colors.h"
#include "rogue/scenes/game_over_scene.h"
#include "rogue/scenes/game_scene.h"
#include "rogue/scenes/title_scene.h"
#include "rogue/scenes/win_scene.h"
#include "rogue/tools/graphics_changer.h"

int main() {
  terminal_open();
  terminal_set(TERMINAL_CFG);
  terminal_bkcolor(PurpleBackground.c1_);
  terminal_refresh();
  terminal_composition(TK_ON);

  Controls controls;
  GraphicsChanger::ChangeGraphics();
  Context ctx{};
  SceneManager sm(ctx);
  sm.Put(TITLE_CONTEXT, new TitleScene(&ctx, controls));
  sm.Put(GAME_CONTEXT, new GameScene(&ctx, controls));
  sm.Put(GAME_OVER_CONTEXT, new GameOverScene(&ctx, controls));
  sm.Put(WIN_CONTEXT, new WinScene(&ctx, controls));

  ctx.scene_ = TITLE_CONTEXT;
  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE) || controls.IsPressed(TK_ESCAPE)) {
      break;
    }
    sm.OnRender();

    controls.Reset();
  }

  sm.OnExit();
  terminal_close();
}
