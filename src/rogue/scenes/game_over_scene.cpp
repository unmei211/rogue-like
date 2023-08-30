#include "rogue/scenes/game_over_scene.h"

#include <constants.h>

void GameOverScene::OnCreate() {}
void GameOverScene::OnExit() {}

void GameOverScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "GAME OVER\nPress Enter to go to the title");
  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->scene_ = TITLE_CONTEXT;
  }
  terminal_refresh();
}

GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
