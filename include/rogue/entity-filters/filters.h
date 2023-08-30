#ifndef INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_
#define INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_

#include "lib/ecs/entity.h"
#include "rogue/components/attributes/collider_component.h"
#include "rogue/components/attributes/name_component.h"
#include "rogue/components/attributes/stomach_component.h"
#include "rogue/components/attributes/texture_component.h"
#include "rogue/components/attributes/transform_component.h"
#include "rogue/components/attributes/wallet_component.h"
#include "rogue/components/capabilities/lift_ability_component.h"
#include "rogue/components/capabilities/movement_component.h"
#include "rogue/components/capabilities/player_control_component.h"
#include "rogue/components/indicators/cost_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/states/removability_component.h"
#include "rogue/components/states/takeable_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/marionette_component.h"
#include "rogue/components/tags/player_component.h"

// Entity is...
bool IsPlayer(const Entity &entity);
bool IsCoin(const Entity &entity);
bool IsFood(const Entity &entity);
bool IsHandledTrap(const Entity &entity);
bool IsItem(const Entity &entity);
bool IsDoor(const Entity &entity);
bool IsMedicine(const Entity &entity);
bool IsMarionette(const Entity &entity);
bool IsEnemy(const Entity &entity);
bool IsTrap(const Entity &entity);
bool IsWall(const Entity &entity);
bool IsTarget(const Entity &entity);
// Entity ignore
bool Deleted(const Entity &entity);
bool Taken(const Entity &entity);

// Entity has
bool HasMovement(const Entity &entity);
bool HasTransform(const Entity &entity);
bool HasPlayerControl(const Entity &entity);
bool HasMovementsCount(const Entity &entity);
bool HasCollider(const Entity &entity);
bool HasLiftAbility(const Entity &entity);
bool HasWallet(const Entity &entity);
bool HasTrapSlot(const Entity &entity);
bool HasTexture(const Entity &entity);
bool HasStomach(const Entity &entity);
bool HasMedicineSlot(const Entity &entity);
bool HasTakeable(const Entity &entity);
bool HasRigidBody(const Entity &entity);
bool HasColor(const Entity &entity);
#endif  // INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_
