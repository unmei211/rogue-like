#ifndef INCLUDE_ROGUE_TOOLS_COLLIDERS_MAP_H_
#define INCLUDE_ROGUE_TOOLS_COLLIDERS_MAP_H_
#include <list>
#include <utility>
#include <vector>

#include "lib/ecs/entity_manager.h"

class CollidersMap {
 private:
  std::vector<std::vector<std::list<Entity*>>> colliders_map_;

 public:
  CollidersMap() = default;
  CollidersMap(int lines, int columns)
      : colliders_map_(std::vector<std::vector<std::list<Entity*>>>(lines, std::vector<std::list<Entity*>>(columns))) {}
  void Clear() {
    colliders_map_.clear();
  }
  void Put(const Vec2& pos, Entity* entity) {
    colliders_map_[pos.y_][pos.x_].push_back(entity);
  }

  std::list<Entity*>& GetAllOnCage(const Vec2& pos) {
    return colliders_map_[pos.y_][pos.x_];
  }
  template<typename Component>
  bool CellContains(const Vec2& pos) {
    for (auto entity : GetAllOnCage(pos)) {
      if (entity->Contains<Component>()) {
        return true;
      }
    }
    return false;
  }
  Entity* Pop(const Vec2& pos, Entity* entity) {
    int x = pos.x_;
    int y = pos.y_;
    if (IsEmpty(pos)) {
      return nullptr;
    }
    if (colliders_map_[y][x].size() == 1 && colliders_map_[y][x].front()->GetId() == entity->GetId()) {
      Entity* temp = colliders_map_[y][x].front();
      colliders_map_[y][x].erase(colliders_map_[y][x].begin());
      return temp;
    }

    for (auto iter = colliders_map_[y][x].begin(); iter != colliders_map_[y][x].end(); iter++) {
      if ((*iter)->GetId() == entity->GetId()) {
        Entity* temp = *iter;
        colliders_map_[y][x].erase(iter);
        return temp;
      }
    }
    return nullptr;
  }
  void MoveTo(const Vec2& new_pos, const Vec2& old_pos, Entity* entity) {
    auto temp = Pop(old_pos, entity);
    if (temp == nullptr) {
      return;
    }
    Put(new_pos, temp);
  }

  bool IsEmpty(const Vec2& pos) {
    return colliders_map_[pos.y_][pos.x_].empty();
  }
  int GetSize(const Vec2& pos) {
    if (IsEmpty(pos)) {
      return 0;
    }
    return colliders_map_[pos.y_][pos.x_].size();
  }
  std::pair<int, int> GetMapSize() {
    return std::pair(colliders_map_[0].size(), colliders_map_.size());
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_COLLIDERS_MAP_H_
