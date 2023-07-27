#ifndef INCLUDE_ROGUE_TOOLS_I_READER_H_
#define INCLUDE_ROGUE_TOOLS_I_READER_H_

#include <string>
#include <vector>
class IReader {
 protected:
  std::vector<std::vector<char>> map_;

 public:
  IReader(int lines, int columns) : map_(std::vector<std::vector<char>>(lines, std::vector<char>(columns))) {}
  virtual void Path(std::string const *path) = 0;
  virtual void Clear() = 0;
  virtual std::vector<std::vector<char>> Get() = 0;
  virtual ~IReader() = default;
};

#endif  // INCLUDE_ROGUE_TOOLS_I_READER_H_
