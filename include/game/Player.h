//
// Created by unmei on 7/15/23.
//

#ifndef INCLUDE_GAME_PLAYER_H_
#define INCLUDE_GAME_PLAYER_H_

#include <queue>
#include <vector>

#include "game/CoinsManager.h"
#include "game/Controls.h"
#include "game/Food.h"
#include "game/FoodManager.h"

class Player {
  float x_;
  float y_;

  int moneys_ = 0;
  int steps_ = 0;

  const char symbol_ = '@';
  const Controls &kControls;
  const CoinsManager &kCoinsManager;
  const FoodManager &kFoodManager;
  void AddFood();
  std::queue<Food> food_queue_;

  void Render() const;
  void Move();
  void GetReward();

 public:
  Player(float x, float y, const Controls &controls, const CoinsManager &coinsManager, const FoodManager &foodManager);
  void Update();

  int GetMoneys();
  int GetSteps();
  Food *GetFood();
  float GetX() const;
  float GetY() const;
};

#endif  // INCLUDE_GAME_PLAYER_H_
