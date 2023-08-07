#ifndef INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_
#define INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_

#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

#include "lib/ecs/entity_manager.h"
#include "lib/ecs/system.h"

class SystemManager {
 private:
  std::map<std::type_index, std::unique_ptr<ISystem>> systems_;
  std::vector<std::type_index> priority_;
  EntityManager *const entity_manager_;

 public:
  explicit SystemManager(EntityManager *entity_manager) : entity_manager_(entity_manager) {}

  template<typename System, typename... Args>
  SystemManager *AddSystem(Args &&...args) {
    systems_.emplace(typeid(System), std::make_unique<System>(entity_manager_, this, std::forward<Args>(args)...));
    priority_.emplace_back(typeid(System));
    return this;
  }

  template<typename System>
  SystemManager *Delete() {
    systems_.erase(typeid(System));
    for (auto iter = priority_.cbegin(); iter != priority_.cend(); iter++) {
      if (*iter == typeid(System)) {
        priority_.erase(iter);
      }
    }
    return this;
  }

  SystemManager *DeleteAll() {
    systems_.clear();
    priority_.clear();
    return this;
  }

  void DisableAll() {
    for (auto &i : systems_) {
      i.second.get()->SetStates(false);
    }
  }
  void EnableAll() {
    for (auto &i : systems_) {
      i.second.get()->SetStates(true);
    }
  }

  template<typename System>
  void Disable() {
    systems_.at(typeid(System))->SetStates(false);
  }

  template<typename System>
  void Enable() {
    systems_.at(typeid(System))->SetStates(true);
  }

  void OnUpdate() {
    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnPreUpdate();
      }
    }
    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnUpdate();
      }
    }
    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnPostUpdate();
      }
    }
  }
};

#endif  // INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_
