#ifndef INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_

#include <queue>

#include "iostream"

class StomachComponent : public IComponent {
  std::queue<Entity*> food_queue;
  bool isNull() {
    return food_queue.empty();
  }

 public:
  void PopFood() {
    if (isNull()) {
      return;
    }
    food_queue.pop();
  }

  Entity* GetFood() {
    if (isNull()) {
      return nullptr;
    }
    return food_queue.front();
  }
  bool IsEmpty() {
    return food_queue.empty();
  }
  void Switch() {
    if (food_queue.size() <= 1) {
      std::cout << "noswitch" << std::endl;
      return;
    }
    std::cout << "switched" << std::endl;
    Entity* temp = food_queue.front();
    food_queue.pop();
    food_queue.push(temp);
  }
  std::queue<Entity*>& GetFoodQueue() {
    return food_queue;
  }
  int GetSize() {
    return static_cast<int>(food_queue.size());
  }

  void AddFood(Entity* const food) {
    food_queue.push(food);
  }

  explicit StomachComponent(Entity* food) {
    food_queue.push(food);
  }
  explicit StomachComponent() = default;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_
