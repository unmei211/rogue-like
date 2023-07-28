#include "rogue/scenes/title_scene.h"

#include <BearLibTerminal.h>

void TitleScene::OnCreate() {}
void TitleScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "Beef-Like game\nPress Enter to start");
  terminal_printf(1, 15, "Press arrows to walk\nPress Q to swap food");
  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->scene_ = "game";
  }
  terminal_refresh();
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
