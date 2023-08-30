#ifndef INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_
#define INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_
#include <set>

#include "lib/ecs/entity.h"
#include "lib/ecs/entity_manager.h"
#include "rogue/colors/colors.h"
#include "rogue/entity-filters/filters.h"
class EntityHandler {
  EntityManager* entity_manager_;

 public:
  Entity* having_control_;
  Entity* marionette_;
  Entity* player_;
  Entity* target_;
  Colors floor = WhiteFloor;
  std::set<Entity*> enemies_;
  std::set<Entity*> hud_;
  std::set<Entity*> traps_;
  void Update() {
    enemies_.clear();
    traps_.clear();
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
      if (IsTrap(entity)) {
        traps_.insert(&entity);
      }
    }
  }
  void findHud() {
    for (auto& entity : *entity_manager_) {
      if (HasTexture(entity) && HasTransform(entity) && entity.Get<TextureComponent>()->symbol_ == '#') {
        auto& pos = entity.Get<TransformComponent>()->pos_;
        if (ToPos(pos.x_) == 0 || ToPos(pos.x_) == 79) {
          hud_.insert(&entity);
          entity.Delete<ColliderComponent>();
          entity.Delete<RigidBodyComponent>();
          entity.Delete<WallComponent>();
          entity.Get<TextureComponent>()->symbol_ = '|';
        } else if (ToPos(pos.y_) == 0 || ToPos(pos.y_) == 3 || ToPos(pos.y_) == 24) {
          hud_.insert(&entity);
          entity.Delete<ColliderComponent>();
          entity.Delete<RigidBodyComponent>();
          entity.Delete<WallComponent>();
          entity.Get<TextureComponent>()->symbol_ = '=';
        }
      }
    }
  }
  EntityHandler() = default;
  explicit EntityHandler(EntityManager* entity_manager) : entity_manager_(entity_manager) {}
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITY_HANDLER_H_
