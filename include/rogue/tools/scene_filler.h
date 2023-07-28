#ifndef INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#define INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#include <string>
#include <vector>

class SceneFiller {
  MapReader* map_reader_;
  EntityCreator* entity_creator_;

 public:
  SceneFiller(MapReader* map_reader, EntityCreator* entity_creator)
      : map_reader_(map_reader), entity_creator_(entity_creator) {}
  void InitMap(const std::string* path) {
    map_reader_->Path(path);
  }
  std::vector<std::vector<char>> GetMap() {
    return map_reader_->Get();
  }
  void Fill(EntityManager* entity_manager) {
    auto temp_map = GetMap();
    for (int i = 0; i < static_cast<int>(temp_map.size()); i++) {
      for (int j = 0; j < static_cast<int>(temp_map[0].size()); j++) {
        char c = temp_map[i][j];
        if (c == '#') {
          entity_creator_->CreateWall(entity_manager->CreateEntity(), Vec2(j, i));
        } else if (c == '$') {
          entity_creator_->CreateCoin(entity_manager->CreateEntity(), Vec2(j, i));
        } else if (c == '@') {
          auto f1 = entity_creator_->CreateFoodItem(entity_manager->CreateEntity(), 'b');
          auto f2 = entity_creator_->CreateFoodItem(entity_manager->CreateEntity(), 'm');
          entity_creator_->CreatePlayer(entity_manager->CreateEntity(), f1, f2, Vec2(j, i));
        } else if (c == 'm' || c == 'g' || c == 'b' || c == 'j') {
          entity_creator_->CreateFoodOnField(entity_manager->CreateEntity(), Vec2(j, i), c);
        }
      }
    }
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
