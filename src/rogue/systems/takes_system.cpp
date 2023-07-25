#include "rogue/systems/takes_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/entity-filters/filters.h"

static bool Filter(const Entity& entity) {
  return HasLiftAbility(entity);
}

static bool PostFilter(const Entity& entity) {
  return HasLiftAbility(entity) && entity.Get<LiftAbilityComponent>()->AnyPicked();
}

TakesSystem::TakesSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
void TakesSystem::PickUp(Entity* picker) {
  if (!(HasCollider(*picker) && picker->Get<ColliderComponent>()->AnyCollision())) {
    return;
  }
  auto cc = picker->Get<ColliderComponent>();
  for (auto& collisions : cc->GetCollisions()) {
    if (!Deleted(*collisions) && HasTakeable(*collisions) && !Taken(*collisions)) {
      picker->Get<LiftAbilityComponent>()->PickUp(collisions);
      collisions->Get<TakeableComponent>()->picked_up_ = true;
      std::cout << collisions->GetId() << " подобран" << std::endl;
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
