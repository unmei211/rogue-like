#include "rogue/scenes/win_scene.h"

#include <iostream>
#include <string>

#include "rogue/tools/stats_parser.h"
void WinScene::OnCreate() {
  stats = StatsParser::GetStringFrom(
      "/home/unmei/Projects/Gardens/starovoytov.vladislav-game/include/rogue/tools/data/win_screen_stats");
}
void WinScene::OnExit() {}

void WinScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "YOU WIN!!!!!!!\nPress Enter to go to the title");
  terminal_printf(40, 1, "YOUR STATS:\n%s\n%s\n%s", stats[0].c_str(), stats[1].c_str(), stats[2].c_str());
  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->scene_ = "title";
  }
  terminal_refresh();
}
WinScene::WinScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
