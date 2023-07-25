#include "rogue/entity-filters/filters.h"

#include <iostream>

// Entity is...
bool IsPlayer(const Entity &entity) {
  return entity.Contains<PlayerComponent>();
}
bool IsCoin(const Entity &entity) {
  return entity.Contains<CoinComponent>();
}

bool IsFood(const Entity &entity) {
  return entity.Contains<FoodComponent>();
}

// Entity ignore
bool Deleted(const Entity &entity) {
  return entity.Contains<RemovabilityComponent>() && entity.Get<RemovabilityComponent>()->must_be_deleted_;
}

bool Taken(const Entity &entity) {
  return entity.Contains<TakeableComponent>() && entity.Get<TakeableComponent>()->picked_up_;
}

// Entity has...
bool HasMovement(const Entity &entity) {
  return entity.Contains<MovementComponent>();
}

bool HasTransform(const Entity &entity) {
  return entity.Contains<TransformComponent>();
}

bool HasPlayerControl(const Entity &entity) {
  return entity.Contains<PlayerControlComponent>();
}

bool HasMovementsCount(const Entity &entity) {
  return entity.Contains<MovementsCountComponent>();
}

bool HasCollider(const Entity &entity) {
  return entity.Contains<ColliderComponent>();
}

bool HasLiftAbility(const Entity &entity) {
  return entity.Contains<LiftAbilityComponent>();
}

bool HasWallet(const Entity &entity) {
  return entity.Contains<WalletComponent>();
}

bool HasTexture(const Entity &entity) {
  return entity.Contains<TextureComponent>();
}

bool HasStomach(const Entity &entity) {
  return entity.Contains<StomachComponent>();
}

bool HasRemovability(const Entity &entity) {
  return entity.Contains<RemovabilityComponent>();
}
