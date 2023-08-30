#ifndef INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_BYPASS_H_
#define INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_BYPASS_H_

#include <map>
#include <queue>
#include <utility>
#include <vector>

#include "lib/math/vec2.h"

class Cell {
 public:
  Vec2 pos_;
  bool scanned = false;
};

class CellWeight : public Cell {
 public:
  int weight = -1;
};

class MapBypass {
  std::queue<Cell*> need_inspect_;
  std::queue<CellWeight*> weight_inspect_;
  std::map<std::pair<int, int>, Cell> available_field_;
  std::map<std::pair<int, int>, CellWeight> weights_field_;
  std::vector<std::vector<char>>* game_map_;
  static bool Respond(char symbol) {
    if (symbol != '#') {
      return true;
    }
    return false;
  }
  Cell* GetCell(const Vec2& pos) {
    if (available_field_.count(std::pair(pos.x_, pos.y_)) <= 0) {
      return nullptr;
    }
    return &available_field_[std::pair(pos.x_, pos.y_)];
  }

  CellWeight* GetWeightCell(const Vec2& pos) {
    if (weights_field_.count(std::pair(pos.x_, pos.y_)) <= 0) {
      return nullptr;
    }
    return &weights_field_[std::pair(pos.x_, pos.y_)];
  }

  void Add(const Vec2& pos) {
    available_field_[std::pair(pos.x_, pos.y_)] = Cell();
    auto cell = GetCell(pos);
    cell->pos_ = pos;
    cell->scanned = false;
    need_inspect_.push(GetCell(pos));
  }
  Cell* Pop() {
    auto cell = need_inspect_.front();
    cell->scanned = true;
    need_inspect_.pop();
    return cell;
  }

 public:
  CellWeight* farthest_;
  Vec2 farthest_pos_;
  std::vector<Vec2> GetAllAvailablePos() {
    std::vector<Vec2> temp;
    for (auto& pair : available_field_) {
      temp.emplace_back(pair.first.first, pair.first.second);
    }
    return temp;
  }
  void SetMap(std::vector<std::vector<char>>* game_map) {
    game_map_ = game_map;
  }

  CellWeight* PopWeight() {
    auto cell_w = weight_inspect_.front();
    weight_inspect_.pop();
    return cell_w;
  }

  void Bypass(const Vec2& start) {
    std::vector<Vec2> checks = {LeftVec2, UpVec2, RightVec2, DownVec2};
    Add(start);
    while (!need_inspect_.empty()) {
      auto cell = Pop();
      for (auto& vec : checks) {
        auto new_pos = cell->pos_ + vec;
        if (GetCell(new_pos) == nullptr && Respond((*game_map_)[new_pos.y_][new_pos.x_])) {
          Add(new_pos);
        }
      }
    }
    for (auto& cell : available_field_) {
      weights_field_[std::pair(cell.first.first, cell.first.second)] = CellWeight();
      weights_field_[std::pair(cell.first.first, cell.first.second)].pos_ = cell.second.pos_;
    }
    GetWeightCell(start)->weight = 0;
    weight_inspect_.push(GetWeightCell(start));
    farthest_ = GetWeightCell(start);
    while (!weight_inspect_.empty()) {
      auto cell_w = PopWeight();
      for (auto& vec : checks) {
        auto next_pos = cell_w->pos_ + vec;
        auto next_cell = GetWeightCell(next_pos);
        if (next_cell != nullptr && next_cell->weight != 0 &&
            (next_cell->weight == -1 || next_cell->weight > cell_w->weight + 1)) {
          next_cell->weight = cell_w->weight + 1;
          weight_inspect_.push(GetWeightCell(next_pos));
          if (next_cell->weight > farthest_->weight) {
            farthest_ = next_cell;
          }
        }
      }
    }
    farthest_pos_ = farthest_->pos_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_RANDOM_MAP_BYPASS_H_
