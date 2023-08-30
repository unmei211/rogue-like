#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_FILLER_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_FILLER_H_

#include <vector>

#include "rogue/tools/map-random/floor.h"
class FloorFiller {
 public:
  static void FillWalls(Floor* floor, std::vector<std::vector<char>>* game_map) {
    Vec2 temp = floor->l_u_vertex_;

    while (ToPos(temp.x_) != ToPos(floor->r_u_vertex_.x_)) {
      if (temp == floor->exist_sockets[1].second || temp == floor->exist_sockets[1].first ||
          temp == floor->enter_socket_.first || temp == floor->enter_socket_.second) {
        (*game_map)[temp.y_][temp.x_] = ' ';
        temp.x_++;
        continue;
      }
      (*game_map)[temp.y_][temp.x_] = '#';
      temp.x_++;
    }
    temp = floor->r_u_vertex_;
    while (ToPos(temp.y_) != ToPos(floor->r_d_vertex_.y_)) {
      if (temp == floor->exist_sockets[2].second || temp == floor->exist_sockets[2].first ||
          temp == floor->enter_socket_.first || temp == floor->enter_socket_.second) {
        (*game_map)[temp.y_][temp.x_] = ' ';
        temp.y_++;
        continue;
      }
      (*game_map)[temp.y_][temp.x_] = '#';
      temp.y_++;
    }
    temp = floor->r_d_vertex_;
    while (ToPos(temp.x_) != ToPos(floor->l_d_vertex_.x_)) {
      if (temp == floor->exist_sockets[3].second || temp == floor->exist_sockets[3].first ||
          temp == floor->enter_socket_.first || temp == floor->enter_socket_.second) {
        (*game_map)[temp.y_][temp.x_] = ' ';
        temp.x_--;
        continue;
      }
      (*game_map)[temp.y_][temp.x_] = '#';
      temp.x_--;
    }
    temp = floor->l_d_vertex_;
    while (ToPos(temp.y_) != ToPos(floor->l_u_vertex_.y_)) {
      if (temp == floor->exist_sockets[0].second || temp == floor->exist_sockets[0].first ||
          temp == floor->enter_socket_.first || temp == floor->enter_socket_.second) {
        (*game_map)[temp.y_][temp.x_] = ' ';
        temp.y_--;
        continue;
      }
      (*game_map)[temp.y_][temp.x_] = '#';
      temp.y_--;
    }
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_FLOOR_FILLER_H_
