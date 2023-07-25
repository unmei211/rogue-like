#ifndef INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_
#define INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_

#include <queue>

class StomachComponent : public IComponent {
 public:
  std::queue<Entity*>food_queue;
};

#endif  // INCLUDE_ROGUE_COMPONENTS_STOMACH_COMPONENT_H_
