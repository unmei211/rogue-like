#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_H_

#include <utility>
#include <vector>

#include "lib/math/vec2.h"
class Tunnel {
  void Swap(const Vec2& swap_checker) {
    if (ToPos(swap_checker.x_) == ToPos(swap_checker.y_)) {
      first_wall_flow_.swap(second_wall_flow_);
    }
    // 6first_wall_flow_.swap(second_wall_flow_);
  }
  void AddFirstFlow() {
    first_wall_flow_.push_back(Vec2(first_wall_flow_.back()) + direction_);
  }
  void AddSecondFlow() {
    second_wall_flow_.push_back(Vec2(second_wall_flow_.back()) + direction_);
  }

  void AddOffsetSecond() {
    AddSecondFlow();
    AddSecondFlow();
    AddSecondFlow();
  }

  void AddOffsetFirst() {
    AddFirstFlow();
    AddFirstFlow();
    AddFirstFlow();
  }

  void Offset(const Vec2& new_direction) {
    Vec2 swap_checker = direction_ + new_direction;
    if (direction_ == DownVec2) {
      if (new_direction == LeftVec2) {
        AddOffsetSecond();
        direction_ = new_direction;
        AddOffsetSecond();
      } else if (new_direction == RightVec2) {
        AddOffsetFirst();
        direction_ = new_direction;
        AddOffsetFirst();
        Swap(swap_checker);
      }

    } else if (direction_ == LeftVec2) {
      if (new_direction == DownVec2) {
        AddOffsetFirst();
        direction_ = new_direction;
        AddOffsetFirst();
      } else if (new_direction == UpVec2) {
        AddOffsetSecond();
        direction_ = new_direction;
        AddOffsetSecond();
        Swap(swap_checker);
      }
    } else if (direction_ == RightVec2) {
      if (new_direction == DownVec2) {
        AddOffsetFirst();
        direction_ = new_direction;
        AddOffsetFirst();
        Swap(swap_checker);
      } else if (new_direction == UpVec2) {
        AddOffsetSecond();
        direction_ = new_direction;
        AddOffsetSecond();
      }
    } else if (direction_ == UpVec2) {
      if (new_direction == RightVec2) {
        AddOffsetFirst();
        direction_ = new_direction;
        AddOffsetFirst();
      } else if (new_direction == LeftVec2) {
        AddOffsetSecond();
        direction_ = new_direction;
        AddOffsetSecond();
        Swap(swap_checker);
      }
    }
  }

 public:
  Vec2 direction_;
  Tunnel(Vec2 first_wall, Vec2 second_wall, Vec2 direction) {
    first_wall_flow_.push_back(first_wall);
    second_wall_flow_.push_back(second_wall);
    direction_ = direction;
    use = true;
    init = true;
  }
  void Clear() {
    first_wall_flow_.clear();
    second_wall_flow_.clear();
  }
  Tunnel() {
    direction_ = ZeroVec2;
    init = false;
    use = false;
  }
  ~Tunnel() = default;
  bool init = false;
  bool use = false;
  bool port = false;
  std::vector<Vec2> first_wall_flow_ = {};
  std::vector<Vec2> second_wall_flow_ = {};
  void CreatePartOfTheTunnel() {
    AddFirstFlow();
    AddSecondFlow();
  }

  void Rotate(Vec2 new_direction) {
    Offset(new_direction);
  }
  static Vec2 GetDirectionOf(int index_number) {
    if (index_number == 0) {
      return LeftVec2;
    }
    if (index_number == 1) {
      return UpVec2;
    }
    if (index_number == 2) {
      return RightVec2;
    }
    if (index_number == 3) {
      return DownVec2;
    }
    return ZeroVec2;
  }
  static std::vector<Vec2> GetAllDirections() {
    std::vector<Vec2> temp;
    temp.push_back(LeftVec2);
    temp.push_back(UpVec2);
    temp.push_back(RightVec2);
    temp.push_back(DownVec2);
    return temp;
  }
  static int GetIndexOfDirection(const Vec2& direction) {
    if (direction == LeftVec2) {
      return 0;
    } else if (direction == UpVec2) {
      return 1;
    } else if (direction == RightVec2) {
      return 2;
    } else if (direction == DownVec2) {
      return 3;
    } else {
      std::cout << "беда нулевое направление" << std::endl;
      return -1;
    }
  }

  void PrintDirections() {
    if (direction_ == ZeroVec2) {
      std::cout << "ZeroVec2" << std::endl;
    }
    if (direction_ == LeftVec2) {
      std::cout << "LeftVec2" << std::endl;
    }
    if (direction_ == UpVec2) {
      std::cout << "UpVec2" << std::endl;
    }
    if (direction_ == RightVec2) {
      std::cout << "RightVec2" << std::endl;
    }
    if (direction_ == DownVec2) {
      std::cout << "DownVec2" << std::endl;
    }
  }

  static void StaticPrintDirections(const Vec2& direction) {
    if (direction == ZeroVec2) {
      std::cout << "ZeroVec2" << std::endl;
    }
    if (direction == LeftVec2) {
      std::cout << "LeftVec2" << std::endl;
    }
    if (direction == UpVec2) {
      std::cout << "UpVec2" << std::endl;
    }
    if (direction == RightVec2) {
      std::cout << "RightVec2" << std::endl;
    }
    if (direction == DownVec2) {
      std::cout << "DownVec2" << std::endl;
    }
  }

  std::pair<Vec2, Vec2> GetConnector() {
    auto temp = std::pair(first_wall_flow_.back(), second_wall_flow_.back());
    if (direction_ == UpVec2) {
      temp.first.x_ -= 1;
      temp.second.x_ += 1;
    } else if (direction_ == DownVec2) {
      temp.first.x_ -= 1;
      temp.second.x_ += 1;
    } else if (direction_ == RightVec2) {
      temp.first.y_ += 1;
      temp.second.y_ -= 1;
    } else if (direction_ == LeftVec2) {
      temp.first.y_ += 1;
      temp.second.y_ -= 1;
    }
    return temp;
  }

  Vec2& GetDirection() {
    return direction_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_H_
