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
    //        for (size_t i = 0; i < priority_.size(); i++) {
    //          std::cout << priority_[i].name() << " [" << i + 1 << "]  ";
    //        }
    //        std::cout << "\n";
    //        std::cout << "\tOnPreUpdate:" << std::endl;

    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnPreUpdate();
      }
    }
    // std::cout << "-----------------------------------------------" << std::endl;
    //    std::cout << "\tOnUpdate: " << std::endl;
    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnUpdate();
      }
    }
    //  std::cout << "-----------------------------------------------" << std::endl;
    //      std::cout << "\tOnPostUpdate:" << std::endl;
    for (auto &p : priority_) {
      if (systems_[p]->is_enabled_) {
        systems_[p]->OnPostUpdate();
      }
    }
    //   std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
  }
};

#endif  // INCLUDE_LIB_ECS_SYSTEM_MANAGER_H_
