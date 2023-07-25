#ifndef INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_
#define INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_

#include "lib/ecs/entity.h"
#include "rogue/components/collider_component.h"
#include "rogue/components/cost_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/lift_ability_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/name_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/removability_component.h"
#include "rogue/components/tags/coin_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/takeable_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"
#include "rogue/components/wallet_component.h"

bool IsPlayer(const Entity &entity);
bool IsCoin(const Entity &entity);
bool IsFood(const Entity &entity);

bool Deleted(const Entity &entity);
bool Taken(const Entity &entity);

#endif  // INCLUDE_ROGUE_ENTITY_FILTERS_FILTERS_H_
