#ifndef INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
#define INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
class FoodConfig {
 private:
  std::map<char, std::pair<std::unique_ptr<std::string>, std::pair<int, std::unique_ptr<Colors>>>> food_configs_;

 public:
  std::vector<char> associates_;
  FoodConfig() {
    food_configs_['g'] = std::pair(std::make_unique<std::string>("hamburger"),
                                   std::pair(3, std::make_unique<Colors>(LightBrownGamburger)));
    food_configs_['m'] =
        std::pair(std::make_unique<std::string>("mango"), std::pair(2, std::make_unique<Colors>(OrangeGreenFoodMango)));
    food_configs_['b'] =
        std::pair(std::make_unique<std::string>("beef"), std::pair(4, std::make_unique<Colors>(RedBeef)));
    food_configs_['j'] =
        std::pair(std::make_unique<std::string>("juice"), std::pair(1, std::make_unique<Colors>(GreenJuice)));
    associates_.push_back('g');
    associates_.push_back('m');
    associates_.push_back('b');
    associates_.push_back('j');
  }
  [[nodiscard]] const std::map<char, std::pair<std::unique_ptr<std::string>, std::pair<int, std::unique_ptr<Colors>>>>&
  GetConfig() const {
    return food_configs_;
  }

  bool Contains(char c) {
    return food_configs_.count(c) > 0;
  }

  std::string* GetName(char symbol) {
    return food_configs_[symbol].first.get();
  }
  int GetNutritions(char symbol) {
    return food_configs_[symbol].second.first;
  }
  Colors* GetColors(char symbol) {
    return food_configs_[symbol].second.second.get();
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_CONFIG_FOOD_CONFIG_H_
