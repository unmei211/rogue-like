#ifndef INCLUDE_LIB_ECS_ENGINE_H_
#define INCLUDE_LIB_ECS_ENGINE_H_

#include <BearLibTerminal.h>

#include <memory>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system_manager.h"
class Engine {
 private:
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;

 public:
  Engine()
      : entity_manager_(std::make_unique<EntityManager>()),
        system_manager_(std::make_unique<SystemManager>(entity_manager_.get())) {}

  EntityManager* GetEntityManager() const {
    return entity_manager_.get();
  }
  SystemManager* GetSystemManager() const {
    return system_manager_.get();
  }

  void OnUpdate() const {
    system_manager_->OnUpdate();
  }
};
#endif  // INCLUDE_LIB_ECS_ENGINE_H_
