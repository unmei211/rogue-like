#ifndef INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_
#define INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_

#include <map>
#include <memory>
#include <typeindex>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system.h"

class SystemManager {
 private:
  std::map<std::type_index, std::unique_ptr<ISystem>> systems_;
  EntityManager *const entity_manager_;

 public:
  explicit SystemManager(EntityManager *entity_manager) : entity_manager_(entity_manager) {}

  template<typename System, typename... Args>
  SystemManager *AddSystem(Args &&...args) {
    systems_.emplace(typeid(System), std::make_unique<System>(entity_manager_, this, std::forward<Args>(args)...));
    return this;
  }

  template<class System>
  SystemManager *Delete() {
    systems_.erase(typeid(System));
    return this;
  }

  SystemManager *DeleteAll() {
    systems_.clear();
    return this;
  }

  template<class System>
  void Disable() const {
    systems_.at(typeid(System))->is_enabled_ = false;
  }

  template<class System>
  void Enable() const {
    systems_.at(typeid(System))->is_enabled_ = true;
  }
  void OnUpdate() {
    for (auto &p : systems_) {
      if (p.second->is_enabled_) {
        p.second->OnPreUpdate();
      }
    }
    for (auto &p : systems_) {
      if (p.second->is_enabled_) {
        p.second->OnUpdate();
      }
    }
    for (auto &p : systems_) {
      if (p.second->is_enabled_) {
        p.second->OnPostUpdate();
      }
    }
  }
};

#endif  // INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_
