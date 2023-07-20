//
// Created by unmei on 17.07.23.
//

#ifndef INCLUDE_GAME_FOODMANAGER_H_
#define INCLUDE_GAME_FOODMANAGER_H_

#include <BearLibTerminal.h>

#include <vector>

#include "game/Food.h"

class FoodOnThePlace {
  Food food_ = Food("beef");
  int x_;
  int y_;

 public:
  explicit FoodOnThePlace(int x, int y, Food food) : food_(food), x_(x), y_(y) {}
  int GetX() {
    return x_;
  }
  int GetY() {
    return y_;
  }
  Food GetFood() {
    return food_;
  }
};

class FoodManager {
  color_t c1 = 0xffff0000;
  color_t c2 = 0xff00aa33;
  color_t c3 = 0xff001100;
  color_t c4 = 0xff00dd00;
  color_t corners_[4] = {c1, c2, c3, c4};

  std::vector<FoodOnThePlace> foods_ = {FoodOnThePlace(8, 8, Food("beef")), FoodOnThePlace(13, 13, Food("mango")),
                                        FoodOnThePlace(10, 8, Food("hamburger"))};
  Food current_food_ = Food("");

  void Render() {
    for (auto &food : foods_) {
      terminal_put_ext(food.GetX(), food.GetY(), 0, 0, '%', corners_);
    }
  }

  void Collision(float x, float y) {
    std::vector<FoodOnThePlace>::iterator it;
    current_food_ = Food("");
    for (it = foods_.begin(); it != foods_.end(); it++) {
      if (it->GetX() == to_pos(x) && it->GetY() == to_pos(y)) {
        current_food_ = it->GetFood();
        foods_.erase(it);
        break;
      }
    }
  }

 public:
  Food GetCurrentFood() const {
    return current_food_;
  }

  void Update(float x, float y) {
    Collision(x, y);
    Render();
  }
};

#endif  // INCLUDE_GAME_FOODMANAGER_H_
