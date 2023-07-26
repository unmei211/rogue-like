#include "rogue/systems/player_food_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/components/breakable_component.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/rigid_body_component.h"
#include "rogue/entity-filters/filters.h"
PlayerFoodSystem::PlayerFoodSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void PlayerFoodSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (IsPlayer(entity) && HasStomach(entity)) {
      // TODO добавить: если не сталкивался с стенами...
      auto stom_com = entity.Get<StomachComponent>();
      auto food = stom_com->GetFood();
      if (entity.Get<MovementComponent>()->direction_ != ZeroVec2 && !stom_com->IsEmpty() && food != nullptr &&
          IsItem(*food) && !entity.Get<RigidBodyComponent>()->AnyRigidCollisions()) {
        auto dur_com = food->Get<DurabilityComponent>();
        if (food->Get<BreakableComponent>()) {
          if (dur_com->current_durability_ > 1) {
            dur_com->current_durability_--;
          } else if (dur_com->current_durability_ <= 1) {
            food->Add<RemovabilityComponent>();
            std::cout << "выкинул еду" << std::endl;
            stom_com->PopFood();
          }
        }
      }
      // TODO отнимать хп
    }
  }
}
