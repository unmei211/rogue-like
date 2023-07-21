//
// Created by unmei on 17.07.23.
//

#include "game/Food.h"

#include <string>

Food::Food(std::string food) : food_(food) {
  current_spent_ = food.length();
}

void Food::TakeAway() {
  current_spent_ = current_spent_ - 0.5;
  // food_.pop_back();
}

size_t Food::GetSpent() const {
  return to_pos(current_spent_);
}
