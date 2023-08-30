#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_GEN_FUN_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_GEN_FUN_H_

#include <constants.h>

#include <queue>
#include <utility>
#include <vector>

#include "rogue/tools/map-random/floor.h"
class GenFun {
 public:
  static void GenerateExistRight(Floor* floor) {
    floor->directions_exist[2] = RightVec2;
    Vec2 temp = Vec2(ToPos(floor->r_u_vertex_.x_), Rand(floor->r_u_vertex_.y_ + 1, floor->r_d_vertex_.y_ - 2));
    floor->exist_sockets[2] = std::pair(temp, Vec2(temp.x_, temp.y_ + 1));
  }
  static void GenerateExistUp(Floor* floor) {
    floor->directions_exist[1] = UpVec2;
    Vec2 temp = Vec2(Rand(floor->l_u_vertex_.x_ + 1, floor->r_u_vertex_.x_ - 2), ToPos(floor->l_u_vertex_.y_));
    floor->exist_sockets[1] = std::pair(Vec2(temp.x_ + 1, temp.y_), temp);
  }
  static void GenerateExistLeft(Floor* floor) {
    floor->directions_exist[0] = LeftVec2;
    Vec2 temp = Vec2(ToPos(floor->l_u_vertex_.x_), Rand(floor->l_u_vertex_.y_ + 1, floor->l_d_vertex_.y_ - 2));
    floor->exist_sockets[0] = std::pair(temp, Vec2(temp.x_, temp.y_ + 1));
  }

  static void SetEnterSocket(Floor* floor, std::pair<Vec2, Vec2>* connector, const Vec2& direction_connector) {
    floor->direction_enter_ = direction_connector * (-1);
    floor->enter_socket_ = *connector;
  }

  static void GenerateExistDown(Floor* floor) {
    floor->directions_exist[3] = DownVec2;
    Vec2 temp = Vec2(Rand(floor->l_d_vertex_.x_ + 1, floor->r_d_vertex_.x_ - 2), ToPos(floor->l_d_vertex_.y_));
    floor->exist_sockets[3] = std::pair(Vec2(temp.x_ + 1, temp.y_), temp);
  }
  static bool FixFloorOutOfBounds(Floor* floor) {
    int diff_x_left = ToPos(GAME_WINDOW_L_U.x_) - ToPos(floor->l_u_vertex_.x_);
    int diff_x_right = ToPos(GAME_WINDOW_R_D.x_) - ToPos(floor->r_d_vertex_.x_);
    int diff_y_up = ToPos(GAME_WINDOW_L_U.y_) - ToPos(floor->l_u_vertex_.y_);
    int diff_y_down = ToPos(GAME_WINDOW_L_D.y_) - ToPos(floor->l_d_vertex_.y_);
    bool recreate = false;
    if (diff_x_left > 0) {
      *floor = Floor(floor->width_ - 1, floor->height_, Vec2(floor->l_u_vertex_.x_ - 1, floor->l_u_vertex_.y_));
      recreate = true;
    }
    if (diff_x_right < 0) {
      *floor = Floor(floor->width_ - 1, floor->height_, floor->l_u_vertex_);
      recreate = true;
    }
    if (diff_y_up > 0) {
      *floor = Floor(floor->width_, floor->height_ - 1, Vec2(floor->l_u_vertex_.x_, floor->l_u_vertex_.y_ + 1));
      recreate = true;
    }
    if (diff_y_down < 0) {
      *floor = Floor(floor->width_, floor->height_ - 1, floor->l_u_vertex_);
      recreate = true;
    }
    if (recreate) {
      return false;
    }
    return true;
  }

  static bool ValidSize(Floor* floor) {
    if (floor->width_ < FLOOR_MIN_WIDTH || floor->height_ < FLOOR_MIN_HEIGHT) {
      return false;
    }
    return true;
  }

  static bool NextAreaAvailableForTunnel(Tunnel* tunnel, std::vector<std::vector<char>>* game_map) {
    Vec2 potential_first_flow = tunnel->first_wall_flow_.back() + tunnel->GetDirection();
    Vec2 potential_second_flow = tunnel->second_wall_flow_.back() + tunnel->GetDirection();

    if (tunnel->GetDirection() == LeftVec2 || tunnel->GetDirection() == RightVec2) {
      if (ToPos(potential_first_flow.y_) < ToPos(potential_second_flow.y_)) {
        Vec2 temp = potential_first_flow;
        if ((*game_map)[temp.y_ + 1][temp.x_] != ' ' || (*game_map)[temp.y_ + 2][temp.x_] != ' ') {
          return false;
        }
      } else {
        Vec2 temp = potential_second_flow;
        if ((*game_map)[temp.y_ + 1][temp.x_] != ' ' || (*game_map)[temp.y_ + 2][temp.x_] != ' ') {
          return false;
        }
      }
      return true;
    } else {
      if (ToPos(potential_first_flow.x_) < ToPos(potential_second_flow.x_)) {
        Vec2 temp = potential_first_flow;
        if ((*game_map)[temp.y_][temp.x_ + 1] != ' ' || (*game_map)[temp.y_][temp.x_ + 2] != ' ') {
          return false;
        }
      } else {
        Vec2 temp = potential_second_flow;
        if ((*game_map)[temp.y_][temp.x_ + 1] != ' ' || (*game_map)[temp.y_][temp.x_ + 2] != ' ') {
          return false;
        }
      }
      return true;
    }
  }
  static void ConnectFloorWithTunnel(std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts,
                                     const Vec2& direction) {
    Vec2 initial_first;
    Vec2 initial_second;
    int point_id;
    if (direction == UpVec2) {
      point_id = 1;
      initial_first = map_parts->back().get()->first.exist_sockets[1].first;
      initial_first.x_ += 1;
      initial_second = map_parts->back().get()->first.exist_sockets[1].second;
      initial_second.x_ -= 1;
    } else if (direction == DownVec2) {
      point_id = 3;
      initial_first = map_parts->back().get()->first.exist_sockets[3].first;
      initial_first.x_ += 1;
      initial_second = map_parts->back().get()->first.exist_sockets[3].second;
      initial_second.x_ -= 1;
    } else if (direction == RightVec2) {
      point_id = 2;
      initial_first = map_parts->back().get()->first.exist_sockets[2].first;
      initial_first.y_ -= 1;
      initial_second = map_parts->back().get()->first.exist_sockets[2].second;
      initial_second.y_ += 1;
    } else if (direction == LeftVec2) {
      point_id = 0;
      initial_first = map_parts->back().get()->first.exist_sockets[0].first;
      initial_first.y_ -= 1;
      initial_second = map_parts->back().get()->first.exist_sockets[0].second;
      initial_second.y_ += 1;
    }

    map_parts->back().get()->second[point_id].first_wall_flow_.push_back(initial_first);
    map_parts->back().get()->second[point_id].second_wall_flow_.push_back(initial_second);
    map_parts->back().get()->second[point_id].direction_ = direction;
    map_parts->back().get()->second[point_id].use = true;
    map_parts->back().get()->second[point_id].init = true;
  }

  static void DeleteExitForFloor(Floor* floor, std::vector<Tunnel>* tunnels, const Vec2& direction) {
    int id = 0;
    for (auto i = tunnels->begin(); i != tunnels->end(); i++) {
      if (i->GetDirection() == direction) {
        (*tunnels)[id].Clear();
        (*tunnels)[id].use = false;
        break;
      }
      id++;
    }
    int id_dir = -1;
    if (direction == LeftVec2) {
      id_dir = 0;
    }
    if (direction == RightVec2) {
      id_dir = 2;
    }
    if (direction == UpVec2) {
      id_dir = 1;
    }
    if (direction == DownVec2) {
      id_dir = 3;
    }
    floor->exist_sockets[id_dir] = std::pair(ZeroVec2, ZeroVec2);
    floor->directions_exist[id_dir] = ZeroVec2;
  }
  static void ViewAllExistDeleteNoValidNextTunnelArea(Floor* floor, std::vector<Tunnel>* tunnels,
                                                      std::vector<std::vector<char>>* game_map) {
    for (auto tunnel = tunnels->begin(); tunnel != tunnels->end(); tunnel++) {
      if (floor->direction_enter_ != tunnel->GetDirection() && tunnel->use && !tunnel->port &&
          !GenFun::NextAreaAvailableForTunnel(&*tunnel, game_map)) {
        GenFun::DeleteExitForFloor(floor, tunnels, tunnel->GetDirection());
      }
    }
  }
  static void DeleteNoValidExistForFloorArea(Floor* floor, std::vector<Tunnel>* tunnels, int id_tunnel) {
    GenFun::DeleteExitForFloor(floor, tunnels, (*tunnels)[id_tunnel].GetDirection());
  }

  static bool FloorSpaceAvailable(Floor* floor, std::vector<std::vector<char>>* game_map) {
    auto& l_u_vertex = floor->l_u_vertex_;
    auto& l_d_vertex = floor->l_d_vertex_;
    auto& r_u_vertex = floor->r_u_vertex_;

    for (int i = l_u_vertex.y_ + 1; i < l_d_vertex.y_; i++) {
      for (int j = l_u_vertex.x_ + 1; j < r_u_vertex.x_; j++) {
        if ((*game_map)[i][j] != ' ') {
          return false;
        }
      }
    }
    return true;
  }

  static void CleanUpObstacleFloor(Floor* floor, std::vector<std::vector<char>>* game_map) {
    auto& l_u_vertex = floor->l_u_vertex_;
    auto& l_d_vertex = floor->l_d_vertex_;
    auto& r_u_vertex = floor->r_u_vertex_;

    for (int i = l_u_vertex.y_ + 1; i < l_d_vertex.y_; i++) {
      for (int j = l_u_vertex.x_ + 1; j < r_u_vertex.x_; j++) {
        if ((*game_map)[i][j] != ' ') {
          (*game_map)[i][j] = ' ';
        }
      }
    }
  }

  static void CleanUpObstacleTunnel(Tunnel* tunnel, std::vector<std::vector<char>>* game_map) {
    int x = tunnel->GetConnector().first.x_;
    int y = tunnel->GetConnector().first.y_;

    if ((*game_map)[y][x] != ' ') {
      (*game_map)[y][x] = ' ';
    }
    x = tunnel->GetConnector().second.x_;
    y = tunnel->GetConnector().second.y_;
    if ((*game_map)[y][x] != ' ') {
      (*game_map)[y][x] = ' ';
    }
  }

  static void PullQueue(std::queue<std::pair<int, Vec2>>* generate_queue,
                        std::vector<std::pair<int, Vec2>>* generate_buffer) {
    for (auto& pair : *generate_buffer) {
      generate_queue->push(pair);
    }
    generate_buffer->clear();
  }

  static void GenerateTunnels(std::queue<std::pair<int, Vec2>>* generate_queue,
                              std::vector<std::pair<int, Vec2>>* generate_buffer,
                              std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts,
                              std::vector<std::vector<char>>* game_map) {
    while (!generate_queue->empty()) {
      auto& in_hand = generate_queue->front();
      auto& tunnel = (*map_parts)[in_hand.first].get()->second[Tunnel::GetIndexOfDirection(in_hand.second)];
      auto length = Rand(TUNNEL_MIN_LENGTH, TUNNEL_MAX_LENGTH);
      bool deleted = false;
      for (int i = 0; i < length; i++) {
        if (tunnel.use && !tunnel.port && GenFun::NextAreaAvailableForTunnel(&tunnel, game_map)) {
          (*map_parts)[in_hand.first]
              .get()
              ->second[Tunnel::GetIndexOfDirection(in_hand.second)]
              .CreatePartOfTheTunnel();
        } else {
          GenFun::DeleteExitForFloor(&(*map_parts)[in_hand.first].get()->first,
                                     &(*map_parts)[in_hand.first].get()->second, tunnel.GetDirection());
          generate_queue->pop();
          deleted = true;
          break;
        }
      }

      if (!deleted) {
        generate_buffer->push_back(generate_queue->front());
        generate_queue->pop();
      }
    }
    PullQueue(generate_queue, generate_buffer);
  }
  static void GenerateDefaultTunnels(std::queue<std::pair<int, Vec2>>* generate_queue,
                                     std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts,
                                     std::vector<std::vector<char>>* game_map) {
    auto length = Rand(TUNNEL_MIN_LENGTH, TUNNEL_MAX_LENGTH);
    for (auto& tunnel : map_parts->back().get()->second) {
      if (!tunnel.use || tunnel.port || tunnel.GetDirection() == ZeroVec2 ||
          map_parts->back().get()->first.direction_enter_ == tunnel.GetDirection() ||
          map_parts->back().get()->first.GetCountOfWorkExist(&map_parts->back().get()->second) <= 0) {
        continue;
      }
      if (GenFun::NextAreaAvailableForTunnel(&tunnel, game_map)) {
        for (int i = 0; i < length; i++) {
          if (GenFun::NextAreaAvailableForTunnel(&tunnel, game_map)) {
            tunnel.CreatePartOfTheTunnel();
          }
        }
        if (map_parts->back().get()->first.direction_enter_ != tunnel.GetDirection() && tunnel.use && !tunnel.port) {
          generate_queue->push(std::pair(map_parts->size() - 1, tunnel.GetDirection()));
        }
      }
    }
  }
  static void PostProcessing(std::vector<std::vector<char>>* game_map,
                             std::vector<std::pair<Floor, std::vector<Tunnel>>>* map_parts) {}
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_GEN_FUN_H_
