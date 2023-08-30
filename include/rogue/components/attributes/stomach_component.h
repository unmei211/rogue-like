#ifndef INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_STOMACH_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_STOMACH_COMPONENT_H_

#include <queue>

#include "iostream"
#include "rogue/tools/i_item_buffer.h"

class StomachComponent : public IComponent, public IItemBuffer {
 public:
  void Switch() {
    if (item_queue_.size() <= 1) {
      return;
    }
    Entity* temp = item_queue_.front();
    item_queue_.pop();
    item_queue_.push(temp);
  }

  explicit StomachComponent(Entity* food) : IItemBuffer(food) {}
  explicit StomachComponent() : IItemBuffer() {}
};

#endif  // INCLUDE_ROGUE_COMPONENTS_ATTRIBUTES_STOMACH_COMPONENT_H_
