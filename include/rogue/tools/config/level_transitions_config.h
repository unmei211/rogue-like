#ifndef INCLUDE_ROGUE_TOOLS_CONFIG_LEVEL_TRANSITIONS_CONFIG_H_
#define INCLUDE_ROGUE_TOOLS_CONFIG_LEVEL_TRANSITIONS_CONFIG_H_

// maybe create IConfig ?
#include <map>
#include <memory>
#include <string>
#include <utility>
class LevelTransitionsConfig {
 private:
  std::map<std::string, std::unique_ptr<std::pair<std::string, std::string>>> level_transitions_;
  bool RequestContains(const std::string& level_name) {
    return level_transitions_.count(level_name) > 0;
  }

 public:
  LevelTransitionsConfig() {
    level_transitions_["level1"] = std::make_unique<std::pair<std::string, std::string>>("title", "level2");
    level_transitions_["level2"] = std::make_unique<std::pair<std::string, std::string>>("level1", "win");
  }

  std::string* GetNextLevelName(const std::string& level_name) {
    if (RequestContains(level_name)) {
      return &level_transitions_[level_name].get()->second;
    }
    return nullptr;
  }

  std::string* GetPrevious(const std::string& level_name) {
    if (RequestContains(level_name)) {
      return &level_transitions_[level_name].get()->first;
    }
    return nullptr;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_CONFIG_LEVEL_TRANSITIONS_CONFIG_H_
