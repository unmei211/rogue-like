//
// Created by unmei on 17.07.23.
//

#ifndef INCLUDE_GAME_FOOD_H_
#define INCLUDE_GAME_FOOD_H_

#include <string>
#include "utils/game-math.h"

class Food {
 private:
  std::string food_;
  float current_spent_;

 public:
  explicit Food(std::string food);

  std::string GetStr() const {
    return food_;
  }

  void TakeAway();
  size_t GetSpent() const;
};

#endif  // INCLUDE_GAME_FOOD_H_
