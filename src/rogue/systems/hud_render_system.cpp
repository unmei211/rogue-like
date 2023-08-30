#include "rogue/systems/hud_render_system.h"

#include <BearLibTerminal.h>
#include <constants.h>

#include <string>

#include "lib/ecs/entity_manager.h"
#include "lib/math/to_pos.h"
#include "rogue/colors/colors.h"
#include "rogue/components/attributes/wallet_component.h"
#include "rogue/components/indicators/durability_component.h"
#include "rogue/components/indicators/floor_counter_component.h"
#include "rogue/components/indicators/movements_count_component.h"
#include "rogue/entity-filters/filters.h"
HudRenderSystem::HudRenderSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                 EntityHandler *entity_handler, const std::string &level_name)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler), level_name_(level_name) {}

void OnHudUpdate(Entity *entity, EntityHandler *entity_handler, const std::string &level_name) {
  if (entity_handler->marionette_ != nullptr) {
    terminal_printf(2, 1, "FOOD HP: %d", entity_handler->marionette_->Get<HPComponent>()->heal_point_);
  } else {
    terminal_printf(2, 1, "HP: %d", entity->Get<HPComponent>()->heal_point_);
  }
  if (entity_handler->marionette_ == nullptr) {
    if (HasMovementsCount(*entity) && level_name != LEVEL_RANDOM_NAME) {
      terminal_printf(17, 1, "STEPS LEFT: %d", entity->Get<MovementsCountComponent>()->aviable_steps_);
    } else {
      terminal_printf(17, 1, "DUNGEON LEVEL: %d", entity->Get<FloorCounterComponent>()->level_number);
    }
    if (HasTrapSlot(*entity)) {
      terminal_printf(53, 1, "TRAPS: x%d", entity->Get<TrapsSlotComponent>()->number_of_traps);
    }
    if (HasWallet(*entity)) {
      terminal_printf(2, 2, "MONEYS: %d", entity->Get<WalletComponent>()->moneys_);
    }
    if (HasTransform(*entity)) {
      terminal_printf(69, 1, "x:%d y:%d", ToPos(entity->Get<TransformComponent>()->pos_.x_),
                      ToPos(entity->Get<TransformComponent>()->pos_.y_));
    }
    if (HasStomach(*entity)) {
      auto red = Red;
      auto food = entity->Get<StomachComponent>()->GetItem();

      terminal_printf(17, 2, "FOOD x%d: ", entity->Get<StomachComponent>()->GetSize());
      if (food != nullptr) {
        auto dur_com = food->Get<DurabilityComponent>();
        int x_hood_food = 26;
        for (int i = 0; i < dur_com->total_; i++) {
          terminal_put(x_hood_food, 2, food->Get<NameComponent>()->name_[i]);
          if (i >= dur_com->total_ - (dur_com->total_ - dur_com->current_)) {
            terminal_put_ext(x_hood_food, 2, 0, 0, '-', red.corners_);
            terminal_put_ext(x_hood_food, 2, 0, 1, '-', red.corners_);
            terminal_put_ext(x_hood_food, 2, 0, 2, '-', red.corners_);
          }
          x_hood_food++;
        }
        terminal_printf(x_hood_food, 2, "  n%d", food->Get<DurabilityComponent>()->multiplier_);
      }
    }
    if (HasMedicineSlot(*entity)) {
      terminal_printf(38, 1, "HEALS: x%d", entity->Get<MedicineSlotComponent>()->numbers_of_medicine_);
    }
  }
}

void HudRenderSystem::OnUpdate() {
  LogPrint(tag_);
  OnHudUpdate(entity_handler_->player_, entity_handler_, level_name_);
}
