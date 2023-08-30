#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_GENERATOR_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_GENERATOR_H_

#include <constants.h>

#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "rogue/math/Rand.h"
#include "rogue/tools/map-random/floor.h"
#include "rogue/tools/map-random/floor_filler.h"
#include "rogue/tools/map-random/gen_fun.h"
#include "rogue/tools/map-random/map_bypass.h"
#include "rogue/tools/map-random/tunnel_filler.h"
#include "rogue/tools/map_reader.h"

static void InitStartFloor(std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts_,
                           std::vector<std::vector<char>>* game_map) {
  int fl_w = Rand(FLOOR_MIN_WIDTH, FLOOR_MAX_WIDTH);
  int fl_h = Rand(FLOOR_MIN_HEIGHT, FLOOR_MAX_HEIGHT);
  Vec2 l_u_vertex = Vec2(Rand(GAME_WINDOW_L_U.x_, GAME_WINDOW_R_U.x_ - FLOOR_MIN_WIDTH),
                         Rand(GAME_WINDOW_L_U.y_, GAME_WINDOW_L_D.y_ - FLOOR_MIN_HEIGHT));
  map_parts_->push_back(std::make_unique<std::pair<Floor, std::vector<Tunnel>>>(Floor(fl_w, fl_h, l_u_vertex),
                                                                                std::vector<Tunnel>(4, Tunnel())));
  while (!GenFun::FixFloorOutOfBounds(&map_parts_->back().get()->first)) {
  }
  bool any_exit = false;
  while (!any_exit) {
    if (Rand(0, 1)) {
      GenFun::GenerateExistLeft(&map_parts_->back().get()->first);
      GenFun::ConnectFloorWithTunnel(map_parts_, LeftVec2);
      any_exit = true;
    }
    if (Rand(0, 1)) {
      GenFun::GenerateExistUp(&map_parts_->back().get()->first);
      GenFun::ConnectFloorWithTunnel(map_parts_, UpVec2);
      any_exit = true;
    }
    if (Rand(0, 1)) {
      GenFun::GenerateExistRight(&map_parts_->back().get()->first);
      GenFun::ConnectFloorWithTunnel(map_parts_, RightVec2);
      any_exit = true;
    }
    if (Rand(0, 1)) {
      GenFun::GenerateExistDown(&map_parts_->back().get()->first);
      GenFun::ConnectFloorWithTunnel(map_parts_, DownVec2);
      any_exit = true;
    }
  }
}

static void InspectStartFloor(std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts,
                              std::vector<std::vector<char>>* game_map,
                              std::queue<std::pair<int, Vec2>>* generate_queue) {
  while (true) {
    GenFun::ViewAllExistDeleteNoValidNextTunnelArea(&map_parts->back().get()->first, &map_parts->back()->second,
                                                    game_map);
    if (map_parts->back().get()->first.GetCountOfWorkExist(&map_parts->back()->second) <= 0) {
      map_parts->clear();
      InitStartFloor(map_parts, game_map);
    } else {
      for (auto& tunnel : map_parts->back()->second) {
        if (tunnel.use && !tunnel.port) {
          generate_queue->push(std::pair(0, tunnel.GetDirection()));
        }
      }
      FloorFiller::FillWalls(&map_parts->back().get()->first, game_map);
      break;
    }
  }
}

static bool InspectDefaultFloor(std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts,
                                std::vector<std::vector<char>>* game_map,
                                std::queue<std::pair<int, Vec2>>* generate_queue) {
  GenFun::ViewAllExistDeleteNoValidNextTunnelArea(&map_parts->back().get()->first, &map_parts->back().get()->second,
                                                  game_map);
  if (map_parts->back().get()->first.GetCountOfWorkExist(&map_parts->back().get()->second) <= 0) {
    return false;
  }
  return true;
}

static void GenerateExistForDefaultFloor(
    std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts) {
  Vec2& ignore = map_parts->back().get()->first.direction_enter_;

  if (ignore != LeftVec2 && (Rand(0, 1))) {
    GenFun::GenerateExistLeft(&map_parts->back().get()->first);
    GenFun::ConnectFloorWithTunnel(map_parts, LeftVec2);
  }
  if (ignore != UpVec2 && (Rand(0, 1))) {
    GenFun::GenerateExistUp(&map_parts->back().get()->first);
    GenFun::ConnectFloorWithTunnel(map_parts, UpVec2);
  }
  if (ignore != RightVec2 && (Rand(0, 1))) {
    GenFun::GenerateExistRight(&map_parts->back().get()->first);
    GenFun::ConnectFloorWithTunnel(map_parts, RightVec2);
  }
  if (ignore != DownVec2 && (Rand(0, 1))) {
    GenFun::GenerateExistDown(&map_parts->back().get()->first);
    GenFun::ConnectFloorWithTunnel(map_parts, DownVec2);
  }
}

class MapGenerator {
  std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>* map_parts_ =
      new std::vector<std::unique_ptr<std::pair<Floor, std::vector<Tunnel>>>>;

  MapReader* map_reader_;
  std::queue<std::pair<int, Vec2>> generate_queue_;
  std::vector<std::pair<int, Vec2>> generate_buffer_;
  std::vector<std::vector<char>>* game_map_;
  std::string GenerateFloorRelativeToSocket(std::pair<Vec2, Vec2> connector, const Vec2& direction_connector) {
    int fl_w = Rand(FLOOR_MIN_WIDTH, FLOOR_MAX_WIDTH);
    int fl_h = Rand(FLOOR_MIN_HEIGHT, FLOOR_MAX_HEIGHT);
    Vec2 l_u_vertex;
    if (direction_connector == LeftVec2 || direction_connector == RightVec2) {
      int temp_y_f = connector.first.y_ - fl_h + 3;
      int temp_y_l = connector.first.y_ - 1;
      int result = Rand(temp_y_f, temp_y_l);
      if (direction_connector == LeftVec2) {
        l_u_vertex = Vec2(ToPos(connector.first.x_) - fl_w + 1, result);
      } else {
        l_u_vertex = Vec2(ToPos(connector.first.x_), result);
      }
    } else if (direction_connector == UpVec2 || direction_connector == DownVec2) {
      auto temp = connector.first;
      connector.first = connector.second;
      connector.second = temp;
      int temp_x_f = connector.first.x_ - fl_w + 3;
      int temp_x_l = connector.first.x_ - 1;
      int result = Rand(temp_x_f, temp_x_l);
      if (direction_connector == UpVec2) {
        l_u_vertex = Vec2(result, ToPos(connector.first.y_) - fl_h + 1);
      } else {
        l_u_vertex = Vec2(result, ToPos(connector.first.y_));
      }
    }
    Floor temp = Floor(fl_w, fl_h, l_u_vertex);
    auto tunnesls = std::vector<Tunnel>(4, Tunnel());
    std::pair<Floor, std::vector<Tunnel>> wtf = std::pair(temp, tunnesls);
    map_parts_->push_back(std::make_unique<std::pair<Floor, std::vector<Tunnel>>>(Floor(fl_w, fl_h, l_u_vertex),
                                                                                  std::vector(4, Tunnel())));
    int tryings = 0;
    while (!GenFun::FixFloorOutOfBounds(&map_parts_->back().get()->first)) {
      if (tryings > 40) {
        map_parts_->pop_back();
        return "no place";
      }
      if (!GenFun::ValidSize(&map_parts_->back().get()->first)) {
        map_parts_->pop_back();
        return "no valid";
      }
      tryings++;
    }
    if (!GenFun::FloorSpaceAvailable(&map_parts_->back().get()->first, game_map_)) {
      map_parts_->pop_back();
      return "space with obstacle";
    }
    GenFun::SetEnterSocket(&map_parts_->back().get()->first, &connector, direction_connector);
    GenerateExistForDefaultFloor(map_parts_);
    if (!InspectDefaultFloor(map_parts_, game_map_, &generate_queue_)) {
      map_parts_->pop_back();
      return "no valid";
    }

    return "accept";
  }

  bool GenerateChildren() {
    auto create_it = generate_queue_.front();
    generate_queue_.pop();
    auto& tunnel = (*map_parts_)[create_it.first].get()->second[Tunnel::GetIndexOfDirection(create_it.second)];

    if (tunnel.use && !tunnel.port) {
      std::string answer = GenerateFloorRelativeToSocket(tunnel.GetConnector(), tunnel.GetDirection());
      if (answer == "no place" || answer == "no valid" || answer == "space with obstacle") {
        for (auto i = 0; i < 100; i++) {
          answer = GenerateFloorRelativeToSocket(tunnel.GetConnector(), tunnel.GetDirection());
          if (answer == "accept") {
            FloorFiller::FillWalls(&map_parts_->back().get()->first, game_map_);
            return true;
          } else if (answer == "no valid" || answer == "no place" || answer == "space with obstacle") {
            continue;
          }
        }
        if (answer == "no valid" || answer == "no place" || answer == "space with obstacle") {
          GenFun::DeleteNoValidExistForFloorArea(&(*map_parts_)[create_it.first].get()->first,
                                                 &(*map_parts_)[create_it.first].get()->second,
                                                 Tunnel::GetIndexOfDirection(create_it.second));
          return false;
        }
      } else {
        FloorFiller::FillWalls(&map_parts_->back().get()->first, game_map_);
        return true;
      }
    }
    return false;
  }
  void GenerateWallsMap() {
    int count_of_room = -1;
    while (count_of_room < 14) {
      map_parts_->clear();
      *game_map_ = map_reader_->Get();
      InitStartFloor(map_parts_, game_map_);
      InspectStartFloor(map_parts_, game_map_, &generate_queue_);
      GenFun::GenerateTunnels(&generate_queue_, &generate_buffer_, map_parts_, game_map_);
      int count = 0;

      while (!generate_queue_.empty()) {
        if (GenerateChildren()) {
          count++;
          GenFun::GenerateDefaultTunnels(&generate_queue_, map_parts_, game_map_);
        }
      }
      count_of_room = count + 1;
    }
    for (auto& part : *map_parts_) {
      for (auto& tunnel : part.get()->second) {
        TunnelFiller::FillWalls(&tunnel, game_map_);
      }
      FloorFiller::FillWalls(&part.get()->first, game_map_);
    }
  }
  void CleanUpWallsMap() {
    for (auto& part : *map_parts_) {
      GenFun::CleanUpObstacleFloor(&part->first, game_map_);
      for (auto& tunnel : part->second) {
        if (tunnel.use) {
          GenFun::CleanUpObstacleTunnel(&tunnel, game_map_);
        }
      }
    }
  }

  std::vector<Vec2> BypassAndGetPositions() {
    MapBypass map_bypass;
    map_bypass.SetMap(game_map_);
    Vec2 start =
        Vec2(map_parts_->back().get()->first.l_u_vertex_.x_ + 1, map_parts_->back().get()->first.l_d_vertex_.y_ - 1);
    map_bypass.Bypass(start);
    return map_bypass.GetAllAvailablePos();
  }

  template<typename Type>
  static int RandIdx(const std::vector<Type>& positions) {
    return Rand(0, positions.size() - 1);
  }

  static void DeleteOnPositions(std::vector<Vec2>* positions, int pos_count) {
    int count = 0;
    for (auto iter = (*positions).begin(); iter != (*positions).end(); iter++) {
      if (count == pos_count) {
        positions->erase(iter);
        return;
      }
      count++;
    }
    std::cout << "нет такой позиции" << std::endl;
  }

  static void DeleteOnPositions(std::vector<Vec2>* positions, const Vec2& vec_pos) {
    for (auto iter = (*positions).begin(); iter != (*positions).end(); iter++) {
      if (*iter == vec_pos) {
        positions->erase(iter);
        return;
      }
    }
    std::cout << "нет такой позиции" << std::endl;
  }

  static void SymbolToMap(char symbol, std::vector<std::vector<char>>* game_map, const Vec2& pos) {
    (*game_map)[pos.y_][pos.x_] = symbol;
  }

  void RandomFillMap(std::vector<std::vector<char>>* game_map) {
    MapBypass map_bypass;
    map_bypass.SetMap(game_map_);
    Vec2 start =
        Vec2(map_parts_->front().get()->first.l_u_vertex_.x_ + 1, map_parts_->front().get()->first.l_d_vertex_.y_ - 1);
    map_bypass.Bypass(start);
    std::vector<Vec2> positions = map_bypass.GetAllAvailablePos();

    int foods_require = static_cast<int>(positions.size() / CELLS_PER_FOOD);
    int coins_require = static_cast<int>(positions.size() / CELLS_PER_COIN);
    int medicine_require = static_cast<int>(positions.size() / CELLS_PER_MEDICINE);
    int enemy_require = static_cast<int>(positions.size() / CELLS_PER_ENEMY);
    int traps_require = static_cast<int>(positions.size() / CELLS_PER_FLOOR_TRAP);
    int handled_traps_require = static_cast<int>(positions.size() / CELLS_PER_HANDLED_TRAP);
    {
      auto& floor = map_parts_->front().get()->first;
      Vec2 first_door = Vec2(Rand(floor.l_u_vertex_.x_ + 1, floor.r_u_vertex_.x_ - 1),
                             Rand(floor.l_u_vertex_.y_ + 1, floor.l_d_vertex_.y_ - 1));
      SymbolToMap('<', game_map_, first_door);
      DeleteOnPositions(&positions, first_door);
    }

    {
      // auto& floor = map_parts_->front().get()->first;
      //      Vec2 second_door = Vec2(Rand(floor.l_u_vertex_.x_ + 1, floor.r_u_vertex_.x_ - 1),
      //                              Rand(floor.l_u_vertex_.y_ + 1, floor.l_d_vertex_.y_ - 1));
      Vec2 second_door = map_bypass.farthest_pos_;
      SymbolToMap('>', game_map_, second_door);
      DeleteOnPositions(&positions, second_door);
    }

    {
      int foods_count = 0;
      FoodConfig food_config;
      while (foods_count != foods_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        auto& associates = food_config.associates_;
        size_t cfg_idx = RandIdx(associates);
        // int i = 0;
        SymbolToMap(associates[cfg_idx], game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        foods_count++;
      }
    }
    {
      int coins_count = 0;
      while (coins_count != coins_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        SymbolToMap('$', game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        coins_count++;
      }
    }
    {
      int traps_count = 0;
      while (traps_count != traps_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        SymbolToMap(',', game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        traps_count++;
      }
    }
    {
      int handled_traps_count = 0;
      while (handled_traps_count != handled_traps_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        SymbolToMap('t', game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        handled_traps_count++;
      }
    }
    {
      int medicine_count = 0;
      while (medicine_count != medicine_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        SymbolToMap('+', game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        medicine_count++;
      }
    }
    {
      int enemy_count = 0;
      while (enemy_count != enemy_require) {
        int pos_idx = RandIdx(positions);
        Vec2& pos = positions[pos_idx];
        SymbolToMap('E', game_map_, pos);
        DeleteOnPositions(&positions, pos_idx);
        enemy_count++;
      }
    }
  }

 public:
  ~MapGenerator() {
    delete map_parts_;
  }
  MapGenerator(std::vector<std::vector<char>>* game_map, MapReader* map_reader)
      : map_reader_(map_reader), game_map_(game_map) {}
  void Generate() {
    GenerateWallsMap();
    CleanUpWallsMap();
    RandomFillMap(game_map_);
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_GENERATOR_H_
