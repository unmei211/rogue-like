//
// Created by unmei on 7/15/23.
//

#include "game/Player.h"

#include "utils/game-math.h"

void Player::Render() const {
  terminal_put(to_pos(x_), to_pos(y_), symbol_);
}

void Player::Move() {
  if (kControls.IsMove()) {
    steps_++;

    food_queue_.front().TakeAway();
    if (food_queue_.front().GetSpent() == 0) {
      food_queue_.pop();
    }
    x_ += kControls.GetDirectionX();
    y_ += kControls.GetDirectionY();
  }
}

void Player::GetReward() {
  moneys_ += kCoinsManager.getCurrentReward();
}

void Player::AddFood() {
  if (kFoodManager.GetCurrentFood().GetStr() != "") {
    this->food_queue_.push(kFoodManager.GetCurrentFood());
  }
}

Player::Player(float x, float y, const Controls& controls, const CoinsManager& coinsManager,
               const FoodManager& foodManager)
    : x_(x), y_(y), kControls(controls), kCoinsManager(coinsManager), kFoodManager(foodManager) {
  Food temp = Food("beef");
  food_queue_.push(temp);
}

float Player::GetX() const {
  return x_;
}

float Player::GetY() const {
  return y_;
}

int Player::GetSteps() {
  return steps_;
}

int Player::GetMoneys() {
  return moneys_;
}

Food* Player::GetFood() {
  return &food_queue_.front();
}

void Player::Update() {
  AddFood();
  GetReward();
  Move();
  Render();
}
