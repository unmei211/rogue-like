#ifndef INCLUDE_ROGUE_TOOLS_I_READER_H_
#define INCLUDE_ROGUE_TOOLS_I_READER_H_

#include <string>
#include <vector>
class IReader {
 public:
  virtual void ReadPath(std::string const *path) = 0;
  virtual void WriteToPath(const std::string &path) = 0;
  virtual void Clear() = 0;
  virtual ~IReader() = default;
};

#endif  // INCLUDE_ROGUE_TOOLS_I_READER_H_
