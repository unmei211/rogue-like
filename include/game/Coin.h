//
// Created by unmei on 17.07.23.
//

#ifndef INCLUDE_GAME_COIN_H_
#define INCLUDE_GAME_COIN_H_

class Coin {
 private:
  float x_;
  float y_;
  int kReward;
  char symbol_;

 public:
  Coin(float x, float y, int reward, char symbol);

  float getX();

  float getY();

  int getReward();

  char getSymbol();
};

#endif  // INCLUDE_GAME_COIN_H_
