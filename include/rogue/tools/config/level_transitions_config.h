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
    level_transitions_[LEVEL1_NAME] = std::make_unique<std::pair<std::string, std::string>>(TITLE_CONTEXT, LEVEL2_NAME);
    level_transitions_[LEVEL2_NAME] = std::make_unique<std::pair<std::string, std::string>>(LEVEL1_NAME, LEVEL3_NAME);
    level_transitions_[LEVEL3_NAME] = std::make_unique<std::pair<std::string, std::string>>(LEVEL2_NAME, WIN_CONTEXT);
    //    level_transitions_[LEVEL_RANDOM_NAME] =
    //        std::make_unique<std::pair<std::string, std::string>>(TITLE_CONTEXT, WIN_CONTEXT);
    level_transitions_[LEVEL_RANDOM_NAME] =
        std::make_unique<std::pair<std::string, std::string>>(TITLE_CONTEXT, LEVEL_RANDOM_NAME_NEXT);
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
