#ifndef INCLUDE_ROGUE_SYSTEMS_LEVEL_TRANSITION_SYSTEM_H_

#define INCLUDE_ROGUE_SYSTEMS_LEVEL_TRANSITION_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"

class LevelTransitionSystem : public ISystem {
 private:
  std::string* load_level_name_;
  EntityHandler* entity_handler_;

 protected:
  std::string tag_ = "LevelTranstionSystem";
  void OnUpdate() override;

 public:
  LevelTransitionSystem(EntityManager* entity_manager, SystemManager* system_manager, std::string* load_level_name,
                        EntityHandler* entity_handler);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_LEVEL_TRANSITION_SYSTEM_H_
