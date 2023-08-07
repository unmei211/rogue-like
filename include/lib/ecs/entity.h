#ifndef INCLUDE_LIB_ECS_ENTITY_H_
#define INCLUDE_LIB_ECS_ENTITY_H_

#include <map>
#include <memory>
#include <typeindex>

#include "lib/ecs/component.h"

class Entity {
  friend class EntityManager;

 private:
  std::map<std::type_index, std::unique_ptr<IComponent>> components_;
  size_t id_ = 0;

 public:
  explicit Entity(size_t id) : id_(id) {}

  template<typename Component, typename... Args>
  Entity* Add(Args&&... args) {
    components_[typeid(Component)] = std::make_unique<Component>(std::forward<Args>(args)...);
    return this;
  }

  size_t GetId() const {
    return id_;
  }

  template<typename Component>
  Component* Get() const {
    auto c = components_.at(typeid(Component)).get();
    return dynamic_cast<Component*>(c);
  }
  bool ContainsAsTypeID(std::type_index idx) const {
    return components_.count(idx) != 0;
  }
  template<typename Component>
  bool Contains() const {
    return components_.count(typeid(Component)) != 0;
  }

  template<typename Component>
  Entity* Delete() {
    components_.erase(typeid(Component));
    return this;
  }
};

#endif  // INCLUDE_LIB_ECS_ENTITY_H_
