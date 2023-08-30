#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_FILLER_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_FILLER_H_
#include <vector>

#include "rogue/tools/map-random/tunnel.h"
class TunnelFiller {
 public:
  static void FillWalls(Tunnel* tunnel, std::vector<std::vector<char>>* game_map) {
    for (auto wall : tunnel->first_wall_flow_) {
      if (tunnel->use) {
        (*game_map)[wall.y_][wall.x_] = '#';
      }
    }
    for (auto wall : tunnel->second_wall_flow_) {
      if (tunnel->use) {
        (*game_map)[wall.y_][wall.x_] = '#';
      }
    }
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_TUNNEL_FILLER_H_
