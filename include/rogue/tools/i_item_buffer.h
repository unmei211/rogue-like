#ifndef INCLUDE_ROGUE_TOOLS_I_ITEM_BUFFER_H_
#define INCLUDE_ROGUE_TOOLS_I_ITEM_BUFFER_H_

#include <queue>

#include "lib/ecs/entity.h"
class IItemBuffer {
 protected:
  std::queue<Entity*> item_queue_;

 public:
  virtual void PopItem() {
    if (IsEmpty()) {
      return;
    }
    item_queue_.pop();
  }
  virtual Entity* GetItem() {
    if (IsEmpty()) {
      return nullptr;
    }
    return item_queue_.front();
  }
  virtual void Add(Entity* const item) {
    item_queue_.push(item);
  }
  std::queue<Entity*>& GetItemQueue() {
    return item_queue_;
  }
  int GetSize() {
    return static_cast<int>(item_queue_.size());
  }
  bool IsEmpty() {
    return item_queue_.empty();
  }
  explicit IItemBuffer(Entity* item);
  explicit IItemBuffer() = default;
};

#endif  // INCLUDE_ROGUE_TOOLS_I_ITEM_BUFFER_H_
