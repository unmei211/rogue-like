#include "rogue/systems/entity_deletion_system.h"

#include "lib/ecs/entity_manager.h"
#include "rogue/entity-filters/filters.h"

EntityDeletionSystem::EntityDeletionSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

static bool Filter(const Entity &entity) {
  return Deleted(entity);
}

void EntityDeletionSystem::OnPostUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (Filter(entity)) {
      std::cout << "DELETE ENTITY" << entity.GetId() << std::endl;
      GetEntityManager().DeleteEntity(entity.GetId());
    }
  }
}
