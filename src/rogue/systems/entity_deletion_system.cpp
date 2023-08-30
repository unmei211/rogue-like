#include "rogue/systems/entity_deletion_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/entity-filters/filters.h"

EntityDeletionSystem::EntityDeletionSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                           EntityMap *const entity_map)
    : ISystem(entity_manager, system_manager), entity_map_(entity_map) {}

void EntityDeletionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (Deleted(entity)) {
      if (HasTexture(entity) && HasTransform(entity)) {
        entity_map_->Pop(entity.Get<TransformComponent>()->pos_.VecToPos(), &entity);
      }
      GetEntityManager().DeleteEntity(entity.GetId());
    }
  }
}
