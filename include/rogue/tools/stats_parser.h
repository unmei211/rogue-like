#ifndef INCLUDE_ROGUE_TOOLS_STATS_PARSER_H_
#define INCLUDE_ROGUE_TOOLS_STATS_PARSER_H_
#include <fstream>
#include <string>
#include <utility>
#include <vector>
class StatsParser {
 public:
  // TODO: make <Template> args...
  static std::vector<std::pair<std::string, std::string>> CastToVec(int steps, int hp, int moneys) {
    std::vector<std::pair<std::string, std::string>> data;
    data.push_back(std::pair("STEPS", std::to_string(steps)));
    data.push_back(std::pair("HP", std::to_string(hp)));
    data.push_back(std::pair("MONEYS", std::to_string(moneys)));
    return data;
  }
  static void WriteDown(const std::string& path, const std::vector<std::pair<std::string, std::string>>& data) {
    std::ofstream fout;
    fout.open(path);
    for (auto cfg_data : data) {
      fout << cfg_data.first << "=" << cfg_data.second << "\n";
    }
  }
  static std::vector<std::string> GetStringFrom(const std::string& path) {
    std::vector<std::string> stats;
    std::ifstream fin;
    fin.open(path);
    char c;
    std::string temp;
    while (fin.get(c)) {
      if (c == EOF) {
        break;
      }
      if (c != '\n') {
        temp.push_back(c);
      } else {
        stats.push_back(temp);
        temp.clear();
      }
    }
    fin.close();
    return stats;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_STATS_PARSER_H_
