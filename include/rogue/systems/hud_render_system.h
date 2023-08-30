#ifndef INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"

class HudRenderSystem : public ISystem {
  EntityHandler* entity_handler_;
  const std::string& level_name_;

 protected:
  std::string tag_ = "HudRenderSystem";
  void OnUpdate() override;

 public:
  HudRenderSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                  const std::string& level_name);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_HUD_RENDER_SYSTEM_H_
