//
// Created by unmei on 17.07.23.
//

#include "game/Coin.h"

Coin::Coin(float x, float y, int reward, char symbol) : x_(x), y_(y), kReward(reward), symbol_(symbol) {}

float Coin::getX() {
  return x_;
}

float Coin::getY() {
  return y_;
}

int Coin::getReward() {
  return kReward;
}

char Coin::getSymbol() {
  return symbol_;
}
