#ifndef INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_

#include <chrono>

#include "lib/ecs/system.h"
#include "lib/math/to_pos.h"
#include "string"

class RenderingSystem : public ISystem {
 private:
  std::chrono::time_point<std::chrono::system_clock> begin;
  std::chrono::time_point<std::chrono::system_clock> end;

 protected:
  std::string tag_ = "RenderingSystem";
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_RENDERING_SYSTEM_H_
