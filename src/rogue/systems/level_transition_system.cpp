#include "rogue/systems/level_transition_system.h"

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system_manager.h"
#include "rogue/entity-filters/filters.h"
LevelTransitionSystem::LevelTransitionSystem(EntityManager* entity_manager, SystemManager* system_manager,
                                             std::string* load_level_name, EntityHandler* entity_handler)
    : ISystem(entity_manager, system_manager), load_level_name_(load_level_name), entity_handler_(entity_handler) {}

void LevelTransitionSystem::OnUpdate() {
  LogPrint(tag_);
  if (entity_handler_->player_->Get<ColliderComponent>()->AnyCollision()) {
    for (auto& desired : entity_handler_->player_->Get<ColliderComponent>()->GetCollisions()) {
      if (IsDoor(*desired)) {
        *load_level_name_ = desired->Get<DoorComponent>()->level_name_;
        break;
      }
    }
  }
}
