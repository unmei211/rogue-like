#include "rogue/systems/take_trap_system.h"

void TakeTrapSystem::OnTakeTrap(Entity* player) {
  for (auto& trap : player->Get<LiftAbilityComponent>()->GetHandPicked()) {
    if (IsHandledTrap(*trap)) {
      player->Get<TrapsSlotComponent>()->number_of_traps++;
      entity_handler_->traps_.erase(trap);
      trap->Add<RemovabilityComponent>();
      trap->Delete<TrapComponent>();
    }
  }
}

void TakeTrapSystem::OnUpdate() {
  if (entity_handler_->player_->Contains<LiftAbilityComponent>() &&
      entity_handler_->player_->Get<LiftAbilityComponent>()->AnyPicked()) {
    OnTakeTrap(entity_handler_->player_);
  }
}
