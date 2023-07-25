#include "rogue/systems/hud_render_system.h"

#include <BearLibTerminal.h>

#include "lib/ecs/entity_manager.h"
#include "rogue/colors/red.h"
#include "rogue/components/durability_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/components/wallet_component.h"
#include "rogue/entity-filters/filters.h"

HudRenderSystem::HudRenderSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}

void HudRenderSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto &entity : GetEntityManager()) {
    if (IsPlayer(entity)) {
      if (HasMovementsCount(entity)) {
        terminal_printf(1, 1, "STEPS: %d", entity.Get<MovementsCountComponent>()->count_);
      }
      if (HasWallet(entity)) {
        terminal_printf(1, 2, "MONEYS: %d", entity.Get<WalletComponent>()->moneys_);
      }
      if (HasStomach(entity)) {
        Red red;
        auto food = entity.Get<StomachComponent>()->GetFood();

        terminal_printf(16, 1, "FOOD: x%d", entity.Get<StomachComponent>()->GetSize());
        if (food != nullptr) {
          auto dur_com = food->Get<DurabilityComponent>();
          int x_hood_food = 25;
          for (int i = 0; i < (dur_com->full_durability_ / 2) + (dur_com->full_durability_) % 2; i++) {
            terminal_put(x_hood_food, 1, food->Get<NameComponent>()->name_[i]);
            if (i >= (dur_com->current_durability_ / 2) + (dur_com->current_durability_ % 2)) {
              terminal_put_ext(x_hood_food, 1, 0, 0, '-', red.corners_);
              terminal_put_ext(x_hood_food, 1, 0, 1, '-', red.corners_);
              terminal_put_ext(x_hood_food, 1, 0, 2, '-', red.corners_);
            }
            x_hood_food++;
          }
        }
      }
    }
  }
}
