#include "rogue/scenes/title_scene.h"

#include <BearLibTerminal.h>

void TitleScene::OnCreate() {}
void TitleScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "Beef-Like game\nPress Enter to start");
  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->scene_ = "game";
  } else if (controls_.IsPressed(TK_K)) {
    ctx_->scene_ = "game_over";
  }
  terminal_refresh();
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
