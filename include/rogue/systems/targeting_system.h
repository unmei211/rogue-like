#ifndef INCLUDE_ROGUE_SYSTEMS_TARGETING_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TARGETING_SYSTEM_H_
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"

struct Vertex {
  explicit Vertex(const Vec2& vec) : vec_(vec) {}
  Vertex() = default;
  Vec2 vec_;
  bool visited_ = false;
  Vertex* from_ = nullptr;
};

class TargetingSystem : public ISystem {
  EntityMap* entity_map_;
  EntityHandler* entity_handler_;
  std::map<std::pair<int, int>, Vertex> map_vertices_;
  std::vector<Vertex*> FindNeighbors(const Vertex& vertex);
  std::vector<Vertex*> BackPath(Vec2* target_pos);
  bool Next(std::queue<Vertex*>* queue, const Vec2& target_pos);
  void BreadthSearch(Entity* enemy, Entity* target);

 protected:
  std::string tag_ = "TargetingSystem";
  void OnUpdate() override;

 public:
  TargetingSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityMap* entity_map,
                  EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TARGETING_SYSTEM_H_
