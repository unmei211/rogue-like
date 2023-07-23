#include "rogue/systems/takes_system.h"

#include "lib/ecs/entity_manager.h"
#include "lib/utils/ignore_entity.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/takeable_component.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<LiftAbilityComponent>() && entity.Contains<ColliderComponent>() &&
         entity.Get<ColliderComponent>()->AnyCollision();
}

static bool PostFilter(const Entity& entity) {
  return entity.Contains<LiftAbilityComponent>() && entity.Get<LiftAbilityComponent>()->AnyPicked();
}

TakesSystem::TakesSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
void TakesSystem::PickUp(Entity* picker) {
  auto cc = picker->Get<ColliderComponent>();
  for (auto& collisions : cc->GetCollisions()) {
    if (!Ignore(*collisions)) {
      if (collisions->Contains<TakeableComponent>() && !collisions->Get<TakeableComponent>()->picked_up_) {
        picker->Get<LiftAbilityComponent>()->PickUp(collisions);
        collisions->Get<TakeableComponent>()->picked_up_ = true;
      }
    }
  }
}

void TakesSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (PostFilter(entity)) {
      entity.Get<LiftAbilityComponent>()->Clear();
    }
  }
}

void TakesSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      PickUp(&entity);
    }
  }
}
