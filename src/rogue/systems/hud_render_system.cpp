#include "rogue/systems/hud_render_system.h"

#include <BearLibTerminal.h>

#include "lib/ecs/entity_manager.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/tags/food_component.h"

HudRenderSystem::HudRenderSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void HudRenderSystem::OnUpdate() {
  for (auto &entity : GetEntityManager()) {
    if (entity.Contains<MovementsCountComponent>() && entity.Contains<PlayerControlComponent>()) {
      terminal_printf(1, 1, "STEPS: %d", entity.Get<MovementsCountComponent>()->count_);
    }
    if (entity.Contains<FoodComponent>()) {
    }
  }
}
