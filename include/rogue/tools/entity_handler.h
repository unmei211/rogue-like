#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_

#include <set>

#include "lib/ecs/entity.h"
#include "lib/ecs/entity_manager.h"
#include "rogue/entity-filters/filters.h"
class EntityHandler {
  EntityManager* entity_manager_;

 public:
  Entity* having_control_;
  Entity* marionette_;
  Entity* player_;
  Entity* target_;
  std::set<Entity*> enemies_;
  void Update() {
    enemies_.clear();
    target_ = nullptr;
    marionette_ = nullptr;
    for (auto& entity : *entity_manager_) {
      if (IsTarget(entity)) {
        target_ = &entity;
      }
      if (HasPlayerControl(entity)) {
        having_control_ = &entity;
      }
      if (IsMarionette(entity)) {
        marionette_ = &entity;
      }
      if (IsPlayer(entity)) {
        player_ = &entity;
      }
      if (IsEnemy(entity)) {
        enemies_.insert(&entity);
      }
    }
  }
  EntityHandler() = default;
  explicit EntityHandler(EntityManager* entity_manager) : entity_manager_(entity_manager) {}
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_
