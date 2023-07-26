#include "rogue/entity-filters/filters.h"

#include <iostream>

#include "rogue/components/item_component.h"
#include "rogue/components/rigid_body_component.h"

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

bool IsItem(const Entity &entity) {
  return entity.Contains<ItemComponent>();
}

// Entity ignore
bool Deleted(const Entity &entity) {
  return entity.Contains<RemovabilityComponent>();
}

bool Taken(const Entity &entity) {
  return entity.Get<TakeableComponent>()->picked_up_;
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

bool HasTakeable(const Entity &entity) {
  return entity.Contains<TakeableComponent>();
}

bool HasRigidBody(const Entity &entity) {
  return entity.Contains<RigidBodyComponent>();
}

