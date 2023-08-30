#ifndef INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_
#include <chrono>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "lib/ecs/system.h"
#include "lib/math/to_pos.h"
#include "lib/utils/controls.h"
#include "rogue/tools/config/graphics_associate.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"
#include "rogue/tools/map-random/map_bypass.h"
#include "string"
class VisionBypass {
  CellWeight* GetCell(const Vec2& pos) {
    if (vision_field_.count(std::pair(pos.x_, pos.y_)) <= 0) {
      return nullptr;
    }
    return &vision_field_[std::pair(pos.x_, pos.y_)];
  }

  void Add(const Vec2& pos) {
    vision_field_[std::pair(pos.x_, pos.y_)] = CellWeight();
    auto cell = GetCell(pos);
    cell->pos_ = pos;
    need_inspect_.push(GetCell(pos));
  }

  CellWeight* Pop() {
    auto cell_w = need_inspect_.front();
    need_inspect_.pop();
    return cell_w;
  }

 public:
  explicit VisionBypass(std::vector<std::vector<char>>* game_map) : game_map_(game_map) {}

  std::vector<std::vector<char>>* game_map_;
  std::queue<CellWeight*> need_inspect_;
  std::map<std::pair<int, int>, CellWeight> vision_field_;
  std::set<std::pair<int, int>> walls_render_;

  void Clean() {
    vision_field_.clear();
    walls_render_.clear();
  }

  void Bypass(const Vec2& start, int vision) {
    std::vector<Vec2> checks = {LeftVec2, UpVec2, RightVec2, DownVec2};
    vision_field_[std::pair(start.x_, start.y_)] = CellWeight();
    auto start_cell = GetCell(start);
    start_cell->weight = 0;
    start_cell->pos_ = start;
    need_inspect_.push(start_cell);
    while (!need_inspect_.empty()) {
      auto cell = Pop();
      for (auto& vec : checks) {
        auto next_pos = cell->pos_ + vec;
        auto next_cell = GetCell(next_pos);
        auto ev_dist = next_pos.Distance(start);
        if (next_cell == nullptr && (*game_map_)[next_pos.y_][next_pos.x_] == '#') {
          walls_render_.insert(std::pair(next_pos.x_, next_pos.y_));
        } else if (next_cell == nullptr && (abs(ev_dist - cell->weight + 1) <= 2) && ev_dist <= vision) {
          vision_field_[std::pair(next_pos.x_, next_pos.y_)] = CellWeight();
          next_cell = &vision_field_[std::pair(next_pos.x_, next_pos.y_)];
          next_cell->weight = cell->weight + 1;
          next_cell->pos_ = next_pos;
          need_inspect_.push(next_cell);
        } else if (next_cell != nullptr && next_cell->weight != 0 &&
                   (next_cell->weight == -1 || next_cell->weight > cell->weight + 1 ||
                    next_cell->weight - vision > cell->weight + 1 - vision)) {
          next_cell->weight = cell->weight + 1;
          need_inspect_.push(GetCell(next_pos));
        }
      }
    }
  }
};

class RenderingSystem : public ISystem {
 private:
  std::chrono::time_point<std::chrono::system_clock> begin;
  std::chrono::time_point<std::chrono::system_clock> end;
  const std::string& level_name_;
  EntityHandler* entity_handler_;
  std::vector<std::vector<char>>* game_map_;
  VisionBypass vision_bypass_;
  EntityMap* entity_map_;
  std::vector<Vec2> default_available_pos;
  GraphicsAssociate* gr_as_;
  std::string fps_;
  bool light = true;
  bool floor_render = true;
  const Controls& controls_;
  void OnLightUpdate();
  void OnVisionUpdate();

 protected:
  std::string tag_ = "RenderingSystem";
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, const std::string& level_name,
                  EntityHandler* entity_handler, std::vector<std::vector<char>>* game_map, EntityMap* entity_map,
                  const Controls& controls, GraphicsAssociate* gr_as);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_
