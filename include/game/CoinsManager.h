//
// Created by unmei on 17.07.23.
//

#ifndef INCLUDE_GAME_COINSMANAGER_H_
#define INCLUDE_GAME_COINSMANAGER_H_

#include <BearLibTerminal.h>

#include <vector>

#include "game/Coin.h"
#include "utils/game-math.h"

class CoinsManager {
 private:
  int current_reward_ = 0;
  std::vector<Coin> coins_ = {{15, 15, 5, '$'}, {20, 20, 5, '$'}, {5, 20, 5, '$'}};

 public:
  CoinsManager();
  void Collision(float x, float y);

  void Render();

  void Update(float x, float y);

  int getCurrentReward() const;
};

#endif  // INCLUDE_GAME_COINSMANAGER_H_
