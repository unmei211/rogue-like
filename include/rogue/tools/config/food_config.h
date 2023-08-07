#ifndef INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
#define INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
class FoodConfig {
 private:
  std::map<char, std::pair<std::unique_ptr<std::string>, int>> food_configs_;

 public:
  FoodConfig() {
    food_configs_['g'] = std::pair(std::make_unique<std::string>("hamburger"), 3);
    food_configs_['m'] = std::pair(std::make_unique<std::string>("mango"), 2);
    food_configs_['b'] = std::pair(std::make_unique<std::string>("beef"), 4);
    food_configs_['j'] = std::pair(std::make_unique<std::string>("juice"), 1);
  }
  [[nodiscard]] const std::map<char, std::pair<std::unique_ptr<std::string>, int>>& GetConfig() const {
    return food_configs_;
  }

  bool Contains(char c) {
    return food_configs_.count(c) > 0;
  }

  std::string* GetName(char symbol) {
    return food_configs_[symbol].first.get();
  }
  int GetNutritions(char symbol) {
    return food_configs_[symbol].second;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
