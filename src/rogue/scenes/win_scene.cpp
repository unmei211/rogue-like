#include "rogue/scenes/win_scene.h"

#include <constants.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "rogue/tools/stats_parser.h"

bool compare(const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) {
  return left.second > right.second;
}

void WinScene::OnCreate() {
  stats = StatsParser::GetStringFrom(WIN_SCREEN_STATS_PATH);
  new_record = false;
  name_writed = false;
  std::ifstream fin;
  fin.open(RANDOM_MAP_TRIGGER_PATH);
  char c;
  if (fin.get(c)) {
    if (c == '1') {
      random_trigger = true;
    } else {
      random_trigger = false;
    }
  } else {
    random_trigger = false;
  }
  fin.close();

  if (!random_trigger) {
    fin.open(SCORES_DEFAULT_PATH);
    std::string temp;
    while (fin.get(c)) {
      if (c == EOF) {
        break;
      }
      if (c != '\n') {
        temp.push_back(c);
      } else {
        std::cout << StatsParser::ParseToInt(temp, '=') << std::endl;
        records_.push_back(std::pair(StatsParser::GetKey(temp), StatsParser::ParseToInt(temp, '=')));
        temp.clear();
      }
    }
    fin.close();
    for (auto scores : records_) {
      int current_score = StatsParser::ParseToInt(stats[2], '=');
      // std::cout << current_score << " " << scores.second << std::endl;
      if (current_score > scores.second) {
        new_record = true;
        break;
      }
    }
  }
}
void WinScene::OnExit() {
  stats.clear();
  records_.clear();
}

void WinScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "YOU WIN!!!!!!!\nPress Enter to go to the title");
  terminal_printf(40, 1, "YOUR STATS:\n%s\n%s\n%s", stats[0].c_str(), stats[1].c_str(), stats[2].c_str());
  if (!random_trigger) {
    if (new_record && !name_writed) {
      terminal_printf(1, 10, "NEW RECORD: %s", stats[2].c_str());
      if (name_writer_.Writed(&nickname_, controls_)) {
        name_writed = true;
        records_.push_back(std::pair(nickname_, StatsParser::ParseToInt(stats[2], '=')));
        std::sort(records_.begin(), records_.end(), compare);

        records_.pop_back();
        nickname_.clear();
        StatsParser::WriteRecords(records_);
        records_.clear();
        return;
      }
      terminal_printf(1, 12, "WRITE NICKNAME: %s", nickname_.c_str());
    }
    terminal_printf(40, 10, "TOP RECORDS:\n1.%s %d\n2.%s %d\n3.%s %d", records_[0].first.c_str(), records_[0].second,
                    records_[1].first.c_str(), records_[1].second, records_[2].first.c_str(), records_[2].second);
  }
  if (controls_.IsPressed(TK_ENTER) && (random_trigger || !new_record || (new_record && name_writed))) {
    ctx_->scene_ = TITLE_CONTEXT;
  }
  terminal_refresh();
}
WinScene::WinScene(Context* ctx, const Controls& controls) : IScene(ctx), controls_(controls) {}
