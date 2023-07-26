#ifndef INCLUDE_ROGUE_TOOLS_MAP_READER_H_
#define INCLUDE_ROGUE_TOOLS_MAP_READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class MapReader {
  std::string path_;

  std::vector<std::vector<char>> map_;

 public:
  MapReader() {
    map_ = std::vector<std::vector<char>>(25, std::vector<char>(80));
  }
  void Read() {
    if (path_ == "") {
      return;
    }
    std::ifstream fin;
    fin.open(path_);
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

  void Path(std::string const *path) {
    path_ = *path;
  }

  std::vector<std::vector<char>> Get() {
    return map_;
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_MAP_READER_H_
