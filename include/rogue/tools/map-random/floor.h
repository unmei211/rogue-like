#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_H_

#include <ctime>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "lib/math/vec2.h"
#include "rogue/math/Rand.h"
#include "rogue/tools/map-random/tunnel.h"

class Floor {
 public:
  int height_;
  int width_;
  Vec2 l_u_vertex_;
  Vec2 r_u_vertex_;
  Vec2 l_d_vertex_;
  Vec2 r_d_vertex_;
  std::pair<Vec2, Vec2> enter_socket_ = std::pair(ZeroVec2, ZeroVec2);
  Vec2 direction_enter_ = ZeroVec2;

  std::vector<std::pair<Vec2, Vec2>> exist_sockets =
      std::vector<std::pair<Vec2, Vec2>>(4, std::pair(ZeroVec2, ZeroVec2));
  std::vector<Vec2> directions_exist = std::vector<Vec2>(4, ZeroVec2);

  int GetCountOfWorkExist(std::vector<Tunnel>* tunnels) {
    int count = 0;
    for (auto& tunnel : *tunnels) {
      if (tunnel.use && !tunnel.port) {
        count++;
      }
    }
    return count;
  }

  bool ContainsPort(std::vector<Tunnel>* tunnels) {
    for (auto& tunnel : *tunnels) {
      if (tunnel.use && tunnel.port) {
        return true;
      }
    }
    return false;
  }

  Floor() = default;
  ~Floor() = default;

  Floor(int width, int height, const Vec2& l_u_vertex) {
    l_u_vertex_ = l_u_vertex;
    l_d_vertex_ = Vec2(l_u_vertex_.x_, l_u_vertex_.y_ + height - 1);
    r_u_vertex_ = Vec2(l_u_vertex_.x_ + width - 1, l_u_vertex_.y_);
    r_d_vertex_ = Vec2(l_u_vertex.x_ + width - 1, l_u_vertex_.y_ + height - 1);
    height_ = height;
    width_ = width;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_H_
