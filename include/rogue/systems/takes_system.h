#ifndef INCLUDE_ROGUE_SYSTEMS_TAKES_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKES_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"

class Entity;

class TakesSystem : public ISystem {
  void PickUp(Entity* picker);

 protected:
  std::string tag_ = "TakesSystem";
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  TakesSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKES_SYSTEM_H_
