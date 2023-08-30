#include "rogue/scenes/title_scene.h"

#include <BearLibTerminal.h>
#include <constants.h>

#include <fstream>

#include "rogue/colors/colors.h"
#include "rogue/tools/graphics_changer.h"
static void state_switch(bool *state) {
  if (!*state) {
    *state = true;
  } else {
    *state = false;
  }
}

void TitleScene::OnCreate() {
  std::ofstream fout;
  fout.open(RANDOM_MAP_TRIGGER_PATH);
  fout << random_trigger;
  fout.close();

  fout.open(GRAPHICS_SET_TRIGGER_PATH);
  fout << graphics_trigger;
  fout.close();
}
void TitleScene::OnRender() {
  terminal_clear();
  terminal_printf(
      1, 1, "%s\nPress Enter to start\nPress H to switch map mode(default/random)\nPress G to change graphics mode",
      GAME_NAME);
  if (random_trigger == true) {
    terminal_bkcolor(GreyBackground.c1_);
    terminal_printf(1, 5, "Mode - random");
  } else {
    terminal_bkcolor(PurpleBackground.c1_);
    terminal_printf(1, 5, "Mode - default");
  }
  if (graphics_trigger) {
    terminal_printf(1, 6, "Graphics mode - SPRITES");
  } else {
    terminal_printf(1, 6, "Graphics mode - ASCII");
  }
  terminal_printf(1, 15,
                  "Press arrows to walk\nPress Q to swap food\nPress E to go for food, distract opponents and collect "
                  "coins\nPress R to heal\nApproach the opponent and click on the arrow towards him to hit");
  if (controls_.IsPressed(TK_H)) {
    state_switch(&random_trigger);
    std::ofstream fout;
    fout.open(RANDOM_MAP_TRIGGER_PATH);
    fout << random_trigger;
    fout.close();
  }
  if (controls_.IsPressed(TK_G)) {
    state_switch(&graphics_trigger);
    std::ofstream fout;
    fout.open(GRAPHICS_SET_TRIGGER_PATH);
    fout << graphics_trigger;
    fout.close();
    // GraphicsChanger::ChangeGraphics(graphics_trigger);
  }
  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->scene_ = GAME_CONTEXT;
  }
  terminal_refresh();
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
