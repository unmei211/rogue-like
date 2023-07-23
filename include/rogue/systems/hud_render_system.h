#ifndef INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"

class HudRenderSystem : public ISystem {
 protected:
  std::string tag_ = "HudRenderSystem";
  void OnUpdate() override;

 public:
  HudRenderSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_
