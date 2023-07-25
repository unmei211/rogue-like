#include "rogue/entity-filters/filters.h"

bool IsPlayer(const Entity &entity) {
  return entity.Contains<PlayerComponent>();
}
bool IsCoin(const Entity &entity) {
  return entity.Contains<CoinComponent>();
}

bool IsFood(const Entity &entity) {
  return entity.Contains<FoodComponent>();
}

bool Deleted(const Entity &entity) {
  return entity.Contains<RemovabilityComponent>() && entity.Get<RemovabilityComponent>()->must_be_deleted_;
}

bool Taken(const Entity &entity) {
  return entity.Contains<TakeableComponent>() && entity.Get<TakeableComponent>()->picked_up_;
}
