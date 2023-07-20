//
// Created by unmei on 17.07.23.
//
#include "game/CoinsManager.h"

#include <vector>


void CoinsManager::Collision(float x, float y) {
  std::vector<Coin>::iterator it;
  current_reward_ = 0;
  for (it = coins_.begin(); it != coins_.end(); it++) {
    if (to_pos(it->getX()) == to_pos(x) && to_pos(it->getY()) == to_pos(y)) {
      current_reward_ = it->getReward();
      coins_.erase(it);
      break;
    }
  }
}

CoinsManager::CoinsManager() {}

int CoinsManager::getCurrentReward() const {
  return current_reward_;
}

void CoinsManager::Render() {
  for (auto &coin : coins_) {
    terminal_put(to_pos(coin.getX()), to_pos(coin.getY()), coin.getSymbol());
  }
}

void CoinsManager::Update(float x, float y) {
  Collision(x, y);
  Render();
}
