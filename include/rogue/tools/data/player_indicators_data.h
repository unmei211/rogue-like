#ifndef INCLUDE_ROGUE_TOOLS_DATA_PLAYER_INDICATORS_DATA_H_
#define INCLUDE_ROGUE_TOOLS_DATA_PLAYER_INDICATORS_DATA_H_

#include <string>

#include "lib/ecs/entity.h"
#include "lib/math/vec2.h"
#include "rogue/components/hp_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/movement_component.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/wallet_component.h"
class PlayerIndicatorsData {
 public:
  ~PlayerIndicatorsData() = default;
  char texture_;
  Vec2 speed_;
  int money_;
  int steps_count_;
  int aviable_steps_;
  int hp_current_;
  int hp_max_;
  std::string from_level_ = "level1";
  PlayerIndicatorsData() {
    texture_ = '@';
    speed_ = OnesVec2;
    money_ = 0;
    steps_count_ = 0;
    aviable_steps_ = 300;
    hp_current_ = 100;
    hp_max_ = 100;
  }
  void SetData(Entity* player) {
    texture_ = player->Get<TextureComponent>()->symbol_;
    speed_ = player->Get<MovementComponent>()->speed_;
    money_ = player->Get<WalletComponent>()->moneys_;
    steps_count_ = player->Get<MovementsCountComponent>()->count_;
    aviable_steps_ = player->Get<MovementsCountComponent>()->aviable_steps_;
    hp_current_ = player->Get<HPComponent>()->heal_point_;
    hp_max_ = player->Get<HPComponent>()->max_heal_point_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_DATA_PLAYER_INDICATORS_DATA_H_
