//
// Created by unmei on 7/15/23.
//

#ifndef INCLUDE_GAME_CONTROLS_H_
#define INCLUDE_GAME_CONTROLS_H_

#include <BearLibTerminal.h>

#include <vector>

class Controls {
  bool is_move_ = false;
  bool is_exit_ = false;
  bool is_take_away_ = false;

  std::vector<int> direction_ = {0, 0};

 public:
  void Update();

  int GetDirectionX() const;

  int GetDirectionY() const;

  bool IsExit() const;

  bool IsMove() const;
};

#endif  // INCLUDE_GAME_CONTROLS_H_
