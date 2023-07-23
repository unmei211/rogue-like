#include "rogue/systems/takes_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/takeable_component.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<LiftAbilityComponent>() && entity.Contains<ColliderComponent>() &&
         entity.Get<ColliderComponent>()->AnyCollision();
}

TakesSystem::TakesSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

void TakesSystem::PickUp(Entity* picker) {
  auto cc = picker->Get<ColliderComponent>();
  for (auto& collisions : cc->GetCollisions()) {
    if (collisions->Contains<TakeableComponent>() && !collisions->Get<TakeableComponent>()->picked_up_) {
      if (!(collisions->Contains<RemovabilityComponent>() &&
            collisions->Get<RemovabilityComponent>()->must_be_deleted_)) {
        picker->Get<LiftAbilityComponent>()->PickUp(collisions);
        collisions->Get<TakeableComponent>()->picked_up_ = true;
      }
    }
  }
}

void TakesSystem::OnUpdate() {
  // LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      PickUp(&entity);
    }
  }
}
