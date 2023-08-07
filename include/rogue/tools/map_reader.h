#ifndef INCLUDE_ROGUE_TOOLS_MAP_READER_H_
#define INCLUDE_ROGUE_TOOLS_MAP_READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rogue/tools/i_reader.h"
class MapReader : public IReader {
  std::vector<std::vector<char>> map_;

 public:
  MapReader(int lines, int columns) : map_(std::vector<std::vector<char>>(lines, std::vector<char>(columns))) {}
  ~MapReader() override {
    Clear();
  }
  void Clear() final {
    map_.clear();
  }
  // TODO:
  void WriteToPath(const std::string& path) final{};

  void ReadPath(std::string const* path) final {
    std::ifstream fin;
    fin.open(*path);
    char c;
    int i = 0;
    int j = 0;
    while (fin.get(c)) {
      if (c == EOF) {
        break;
      }
      if (j < 80) {
        map_[i][j] = c;
        j++;
      } else {
        j = 0;
        i++;
      }
    }
    fin.close();
  }

  std::vector<std::vector<char>> Get() {
    return map_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_READER_H_
