#ifndef INCLUDE_ROGUE_TOOLS_ENTITYMAPSHANDLER_H_
#define INCLUDE_ROGUE_TOOLS_ENTITYMAPSHANDLER_H_

#include <constants.h>

#include <map>
#include <string>

#include "rogue/tools/entity_map.h"

class EntityMapsHandler {
 private:
  std::map<std::string, EntityMap> maps_handler_;

 public:
  EntityMapsHandler() = default;
  EntityMap* GetMap(const std::string& name) {
    if (maps_handler_.count(name) == 0) {
      return nullptr;
    }
    return &maps_handler_[name];
  }
  void CreateMap(const std::string& name, const int lines, const int columns) {
    maps_handler_[name] = EntityMap(lines, columns);
  }
  void ClearMap(const std::string& name) {
    maps_handler_[name].Clear();
  }
  void DeleteMap(const std::string& name) {
    if (!HandlerContains(name)) {
      return;
    }
    maps_handler_[name].Clear();
    maps_handler_.erase(name);
  }
  void ReplaceMap(const std::string& name, const int lines, const int columns) {
    DeleteMap(name);
    CreateMap(name, lines, columns);
  }
  bool HandlerContains(const std::string& name) {
    if (maps_handler_.empty()) {
      return false;
    }
    return maps_handler_.count(name) >= 1;
  }
  int GetMapsCount() {
    return static_cast<int>(maps_handler_.size());
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_ENTITYMAPSHANDLER_H_
