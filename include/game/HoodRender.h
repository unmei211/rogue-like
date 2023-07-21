//
// Created by unmei on 17.07.23.
//

#ifndef INCLUDE_GAME_HOODRENDER_H_
#define INCLUDE_GAME_HOODRENDER_H_
#include <BearLibTerminal.h>

#include <iostream>
#include <string>
#include <vector>

#include "game/Food.h"

class HoodRender {
  color_t c1 = 0xffff0000;
  color_t c2 = 0xffff0000;
  color_t c3 = 0xffff0000;
  color_t c4 = 0xffff0000;
  color_t corners_[4] = {c1, c2, c3, c4};

  // cor* = 0xffff0000;
  // color_t* corn = corners_;
  //  color_t[3] = {120,3,2,1};
 public:
  void Render(int moneys, int steps, Food food) {
    terminal_printf(1, 1, "moneys: %d", moneys);
    terminal_printf(1, 2, "steps: %d", steps);
    int x_food_coord_for_char = 22;

    terminal_printf(15, 1, "food:");
    for (size_t i = 0; i < food.GetStr().length(); i++) {
      terminal_put(x_food_coord_for_char, 1, food.GetStr()[i]);
      if (i >= food.GetSpent()) {
        terminal_put_ext(x_food_coord_for_char, 1, 0, 0, '-', corners_);
        terminal_put_ext(x_food_coord_for_char, 1, 0, 1, '-', corners_);
        terminal_put_ext(x_food_coord_for_char, 1, 0, 2, '-', corners_);
        // terminal_put(x_food_coord_for_char, 1, '-');
      }
      x_food_coord_for_char++;
    }
  }
};

#endif  // INCLUDE_GAME_HOODRENDER_H_
