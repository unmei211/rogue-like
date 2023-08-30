#include "rogue/entity-filters/filters.h"

#include <iostream>
#include <string>

#include "rogue/components/attributes/color_component.h"
#include "rogue/components/attributes/medicine_slot_component.h"
#include "rogue/components/attributes/rigid_body_component.h"
#include "rogue/components/attributes/traps_slot_component.h"
#include "rogue/components/tags/door_component.h"
#include "rogue/components/tags/enemy_component.h"
#include "rogue/components/tags/item_component.h"
#include "rogue/components/tags/loot_component.h"
#include "rogue/components/tags/marionette_component.h"
#include "rogue/components/tags/medicine_component.h"
#include "rogue/components/tags/target_component.h"
#include "rogue/components/tags/trap_component.h"
#include "rogue/components/tags/wall_component.h"

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

bool IsHandledTrap(const Entity& entity) {
  return entity.Contains<TrapComponent>() && entity.Contains<TakeableComponent>();
}

bool IsItem(const Entity &entity) {
  return entity.Contains<ItemComponent>();
}
bool IsDoor(const Entity &entity) {
  return entity.Contains<DoorComponent>();
}
bool IsMedicine(const Entity &entity) {
  return entity.Contains<MedicineComponent>();
}
bool IsMarionette(const Entity &entity) {
  return entity.Contains<MarionetteComponent>();
}
bool IsEnemy(const Entity &entity) {
  return entity.Contains<EnemyComponent>();
}

bool IsTrap(const Entity &entity) {
  return entity.Contains<TrapComponent>();
}

bool IsWall(const Entity &entity) {
  return entity.Contains<WallComponent>();
}

bool IsTarget(const Entity &entity) {
  return entity.Contains<TargetComponent>();
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


bool HasTrapSlot(const Entity& entity) {
  return entity.Contains<TrapsSlotComponent>();
}

bool HasTexture(const Entity &entity) {
  return entity.Contains<TextureComponent>();
}

bool HasStomach(const Entity &entity) {
  return entity.Contains<StomachComponent>();
}

bool HasMedicineSlot(const Entity &entity) {
  return entity.Contains<MedicineSlotComponent>();
}

bool HasTakeable(const Entity &entity) {
  return entity.Contains<TakeableComponent>();
}

bool HasRigidBody(const Entity &entity) {
  return entity.Contains<RigidBodyComponent>();
}
bool HasColor(const Entity &entity) {
  return entity.Contains<ColorComponent>();
}
