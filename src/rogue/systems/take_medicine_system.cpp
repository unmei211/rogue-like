#include "rogue/systems/take_medicine_system.h"

TakeMedicineSystem::TakeMedicineSystem(EntityManager *entity_manager, SystemManager *system_manager,
                                       EntityHandler *entity_handler, EntityMap *entity_map)
    : ISystem(entity_manager, system_manager), entity_handler_(entity_handler), entity_map_(entity_map) {}

void TakeMedicineSystem::OnTakeMedicine(Entity *entity) {
  for (auto &loot : entity->Get<LiftAbilityComponent>()->GetHandPicked()) {
    if (IsMedicine(*loot) && !IsItem(*loot)) {
      loot->Delete<LootComponent>();
      loot->Add<RemovabilityComponent>();
      entity->Get<MedicineSlotComponent>()->numbers_of_medicine_++;
    }
  }
}

void TakeMedicineSystem::OnUpdate() {
  LogPrint(tag_);
  if (entity_handler_->player_->Contains<LiftAbilityComponent>() &&
      entity_handler_->player_->Get<LiftAbilityComponent>()->AnyPicked()) {
    OnTakeMedicine(entity_handler_->player_);
  }
}
