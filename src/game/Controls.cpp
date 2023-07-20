//
// Created by unmei on 7/15/23.
//

#include "game/Controls.h"

void Controls::Update() {
  is_move_ = false;
  while (terminal_has_input()) {
    int event = terminal_read();

    if (event == TK_CLOSE || event == TK_ESCAPE) {
      is_exit_ = true;
      break;
    }

    if (event == TK_DOWN) {
      is_move_ = true;
      direction_[0] = 0;
      direction_[1] = 1;
    } else if (event == TK_UP) {
      is_move_ = true;

      direction_[0] = 0;
      direction_[1] = -1;
    } else if (event == TK_LEFT) {
      is_move_ = true;

      direction_[0] = -1;
      direction_[1] = 0;
    } else if (event == TK_RIGHT) {
      is_move_ = true;

      direction_[0] = 1;
      direction_[1] = 0;
    }
  }
}

int Controls::GetDirectionX() const {
  return direction_[0];
}

int Controls::GetDirectionY() const {
  return direction_[1];
}

bool Controls::IsExit() const {
  return is_exit_;
}

bool Controls::IsMove() const {
  return is_move_;
}
