#ifndef INCLUDE_ROGUE_SCENES_WIN_SCENE_H_
#define INCLUDE_ROGUE_SCENES_WIN_SCENE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"
class NameWriter {
  std::map<size_t, char> associate_;
  char filter(const Controls& controls) {
    for (auto& symbol : associate_) {
      if (controls.IsPressed(symbol.first)) {
        if (associate_.count(symbol.first) >= 1) {
          return symbol.second;
        }
      }
    }
    return '\n';
  }

 public:
  NameWriter() {
    size_t temp = TK_A;
    char temp_associate = 0x41;
    while (temp != TK_1) {
      associate_[temp] = temp_associate;
      temp_associate++;
      temp++;
    }
  }
  bool Writed(std::string* buff_name, const Controls& controls) {
    if (controls.IsPressed(TK_ENTER) && buff_name->length() <= 12 && buff_name->length() >= 3) {
      return true;
    }
    if (controls.IsPressed(TK_BACKSPACE) && !buff_name->empty()) {
      buff_name->pop_back();
      return false;
    }
    if (filter(controls) != '\n') {
      buff_name->push_back(filter(controls));
      return false;
    }
    return false;
  }
};

class WinScene : public IScene {
  const Controls& controls_;
  NameWriter name_writer_ = NameWriter();
  std::vector<std::string> stats;
  std::vector<std::pair<std::string, int>> records_;
  bool random_trigger = false;
  std::string nickname_;
  bool name_writed = false;
  bool new_record = false;

 public:
  WinScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_WIN_SCENE_H_
