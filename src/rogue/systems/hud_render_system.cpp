#include "rogue/systems/hud_render_system.h"

#include <BearLibTerminal.h>

#include "lib/ecs/entity_manager.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/player_control_component.h"
#include "rogue/components/tags/food_component.h"
#include "rogue/components/tags/player_component.h"
#include "rogue/components/wallet_component.h"

HudRenderSystem::HudRenderSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void HudRenderSystem::OnUpdate() {
  for (auto &entity : GetEntityManager()) {
    if (entity.Contains<PlayerComponent>()) {
      if (entity.Contains<MovementsCountComponent>()) {
        terminal_printf(1, 1, "STEPS: %d", entity.Get<MovementsCountComponent>()->count_);
      }
      if (entity.Contains<WalletComponent>()) {
        terminal_printf(1, 2, "MONEYS: %d", entity.Get<WalletComponent>()->moneys_);
      }
    }
  }
}
