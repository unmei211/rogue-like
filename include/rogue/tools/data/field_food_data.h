#ifndef INCLUDE_ROGUE_TOOLS_DATA_FIELD_FOOD_DATA_H_
#define INCLUDE_ROGUE_TOOLS_DATA_FIELD_FOOD_DATA_H_

#include "lib/math/vec2.h"
struct LootFoodData {
  char texture_;
  int current_;
  int multiplier_;
  int total_;
  Vec2 pos_;
};

class FieldFoodData {};

#endif  // INCLUDE_ROGUE_TOOLS_DATA_FIELD_FOOD_DATA_H_
