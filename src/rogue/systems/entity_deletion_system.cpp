#include "rogue/systems/entity_deletion_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/entity-filters/filters.h"

EntityDeletionSystem::EntityDeletionSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                           CollidersMap *const colliders_map)
    : ISystem(entity_manager, system_manager), colliders_map_(colliders_map) {}

void EntityDeletionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (Deleted(entity)) {
      if (HasCollider(entity)) {
        colliders_map_->Pop(entity.Get<TransformComponent>()->pos_.VecToPos(), &entity);
      }
      GetEntityManager().DeleteEntity(entity.GetId());
    }
  }
}
