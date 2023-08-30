#include "rogue/systems/game_over_system.h"

#include <constants.h>

#include "rogue/entity-filters/filters.h"
GameOverSystem::GameOverSystem(EntityManager *const entity_manager, SystemManager *const system_manager, Context *ctx,
                               EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler), ctx_(ctx) {}

void GameOverSystem::OnUpdate() {
  OnSystemUpdate(entity_handler_->player_);
}

void GameOverSystem::OnSystemUpdate(Entity *entity) {
  if (entity->Get<MovementsCountComponent>()->aviable_steps_ <= 0 || entity->Get<HPComponent>()->heal_point_ <= 0) {
    GameOver();
  }
}
void GameOverSystem::GameOver() {
  ctx_->scene_ = GAME_OVER_CONTEXT;
}
