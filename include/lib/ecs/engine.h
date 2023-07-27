#ifndef INCLUDE_LIB_ECS_ENGINE_H_
#define INCLUDE_LIB_ECS_ENGINE_H_

#include <BearLibTerminal.h>

#include <memory>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system_manager.h"
#include "rogue/tools/entity_creator.h"
#include "rogue/tools/map_reader.h"
class Engine {
 private:
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;
  std::unique_ptr<MapReader> map_reader_ = std::make_unique<MapReader>(25, 80);
  // MapReader* map_reader_;

 public:
  Engine()
      : entity_manager_(std::make_unique<EntityManager>()),
        system_manager_(std::make_unique<SystemManager>(entity_manager_.get())),
        map_reader_(new MapReader(25, 80)) {}

  EntityManager* GetEntityManager() const {
    return entity_manager_.get();
  }
  SystemManager* GetSystemManager() const {
    return system_manager_.get();
  }
  MapReader* GetMapReader() const {
    return map_reader_.get();
    // return map_reader_.get();
  }
  void OnUpdate() const {
    system_manager_->OnUpdate();
  }
};
#endif  // INCLUDE_LIB_ECS_ENGINE_H_
