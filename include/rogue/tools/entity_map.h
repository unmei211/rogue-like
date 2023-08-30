#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_MAP_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_MAP_H_
#include <list>
#include <utility>
#include <vector>

#include "lib/ecs/entity_manager.h"

class EntityMap {
 private:
  std::vector<std::vector<std::list<Entity*>>> entity_map_;

 public:
  EntityMap() = default;
  EntityMap(int lines, int columns)
      : entity_map_(std::vector<std::vector<std::list<Entity*>>>(lines, std::vector<std::list<Entity*>>(columns))) {}
  void Clear() {
    if (entity_map_.empty()) {
      return;
    }
    entity_map_ = std::vector<std::vector<std::list<Entity*>>>(entity_map_.size(),
                                                               std::vector<std::list<Entity*>>(entity_map_[0].size()));
  }
  void Put(const Vec2& pos, Entity* entity) {
    entity_map_[pos.y_][pos.x_].push_back(entity);
  }
  template<typename Component>
  std::list<Entity*> GetAllOfTypeOnCell(const Vec2& pos) {
    std::list<Entity*> list_of_type;
    for (auto entity : entity_map_[pos.y_][pos.x_]) {
      if (entity->Contains<Component>()) {
        list_of_type.push_back(entity);
      }
    }
    return list_of_type;
  }

  std::list<Entity*>& GetAllOnCage(const Vec2& pos) {
    return entity_map_[pos.y_][pos.x_];
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
    if (entity_map_[y][x].size() == 1 && entity_map_[y][x].front()->GetId() == entity->GetId()) {
      Entity* temp = entity_map_[y][x].front();
      entity_map_[y][x].erase(entity_map_[y][x].begin());
      return temp;
    }

    for (auto iter = entity_map_[y][x].begin(); iter != entity_map_[y][x].end(); iter++) {
      if ((*iter)->GetId() == entity->GetId()) {
        Entity* temp = *iter;
        entity_map_[y][x].erase(iter);
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
    return entity_map_[pos.y_][pos.x_].empty();
  }
  template<typename Component>
  int GetCountOfTypePerCell(const Vec2& pos) {
    if (IsEmpty(pos)) {
      return 0;
    }
    int count;
    for (auto entity : GetAllOnCage(pos)) {
      if (entity->Contains<Component>()) {
        count++;
      }
    }
    return count;
  }
  int GetCountPerCell(const Vec2& pos) {
    if (IsEmpty(pos)) {
      return 0;
    }
    return entity_map_[pos.y_][pos.x_].size();
  }
  std::pair<int, int> GetMapSize() {
    return std::pair(entity_map_[0].size(), entity_map_.size());
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_MAP_H_
