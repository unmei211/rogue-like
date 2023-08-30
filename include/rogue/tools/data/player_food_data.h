#ifndef INCLUDE_ROGUE_TOOLS_DATA_PLAYER_FOOD_DATA_H_
#define INCLUDE_ROGUE_TOOLS_DATA_PLAYER_FOOD_DATA_H_

#include <queue>
#include <vector>

struct FoodData {
  char texture_;
  int current_;
  int multiplier_;
  int total_;
};

class PlayerFoodData {
 private:
  std::vector<FoodData> food_data_;

 public:
  PlayerFoodData() {
    food_data_.push_back(FoodData{'b', 4, 3, 4});
    food_data_.push_back(FoodData{'m', 5, 2, 5});
  }
  std::vector<FoodData>* GetFoodData() {
    return &food_data_;
  }
  void SetData(std::queue<Entity*> food_queue) {
    food_data_.clear();
    while (!food_queue.empty()) {
      auto food = food_queue.front();
      auto stats = food->Get<DurabilityComponent>();
      food_data_.push_back(
          FoodData{food->Get<TextureComponent>()->symbol_, stats->current_, stats->multiplier_, stats->total_});
      food_queue.pop();
    }
  }
  void Clear() {
    food_data_.clear();
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_DATA_PLAYER_FOOD_DATA_H_
