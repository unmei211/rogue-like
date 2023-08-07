#include "rogue/systems/player_food_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/components/breakable_component.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/entity-filters/filters.h"
PlayerFoodSystem::PlayerFoodSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                   EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler) {}

void PlayerFoodSystem::OnPlayerFoodUpdate(Entity *entity) {
  if (!HasStomach(*entity)) {
    return;
  }
  auto stomach_com = entity->Get<StomachComponent>();
  auto food = stomach_com->GetFood();
  if (entity->Get<MovementComponent>()->direction_ != ZeroVec2 && !stomach_com->IsEmpty() && food != nullptr &&
      IsItem(*food) && !(HasRigidBody(*entity) && entity->Get<RigidBodyComponent>()->AnyRigidCollisions())) {
    auto dur_com = food->Get<DurabilityComponent>();
    if (food->Get<BreakableComponent>()) {
      if (dur_com->current_multiplied_ > 1) {
        dur_com->Subtract(1);
      } else if (dur_com->current_multiplied_ <= 1) {
        food->Add<RemovabilityComponent>();
        stomach_com->PopFood();
      }
    }
  }
}

void PlayerFoodSystem::OnUpdate() {
  LogPrint(tag_);
  OnPlayerFoodUpdate(entity_handler_->player_);
}
