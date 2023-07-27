#ifndef INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#define INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
#include <string>
#include <vector>

class SceneFiller {
  MapReader* map_reader_;

 public:
  explicit SceneFiller(MapReader* map_reader) : map_reader_(map_reader) {}
  void InitMap(const std::string* path) {
    map_reader_->Path(path);
  }
  std::vector<std::vector<char>> GetMap() {
    return map_reader_->Get();
  }
  void Fill(EntityManager* entity_manager, EntityCreator* entity_creator) {
    auto temp_map = GetMap();

    for (size_t i = 0; i < temp_map.size(); i++) {
      for (size_t j = 0; j < temp_map[0].size(); j++) {
        char c = temp_map[i][j];
        if (c == '#') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(WallComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)));
        } else if (c == '@') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(PlayerComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)));
        } else if (c == '$') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(CoinComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)));
        } else if (c == '%') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(FoodComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)), "mango", c);
        } else if (c == 'g') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(FoodComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)), "hamburger", c);
        } else if (c == 'b') {
          entity_creator->CreateEntity(entity_manager->CreateEntity(), typeid(FoodComponent),
                                       Vec2(static_cast<int>(j), static_cast<int>(i)), "beef", c);
        }
      }
    }
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_SCENE_FILLER_H_
