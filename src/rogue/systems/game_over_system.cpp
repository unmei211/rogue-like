#include "rogue/systems/game_over_system.h"

#include "rogue/entity-filters/filters.h"
GameOverSystem::GameOverSystem(EntityManager *const entity_manager, SystemManager *const system_manager, Context *ctx)
    : ISystem(entity_manager, system_manager), ctx_(ctx) {}

void GameOverSystem::OnUpdate() {
  for (auto &entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
      OnSystemUpdate(&entity);
    }
  }
}
void GameOverSystem::OnSystemUpdate(Entity *entity) {
  if (entity->Get<MovementsCountComponent>()->aviable_steps_ <= 0) {
    GameOver();
  }
}
void GameOverSystem::GameOver() {
  ctx_->scene_ = "game_over";
}
