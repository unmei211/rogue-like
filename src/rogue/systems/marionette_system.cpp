#include "rogue/systems/marionette_system.h"

#include "lib/ecs/system_manager.h"
#include "rogue/entity-filters/filters.h"

MarionetteSystem::MarionetteSystem(EntityManager *entity_manager, SystemManager *system_manager,
                                   EntityHandler *entity_handler, CollidersMap *colliders_map)
    : ISystem(entity_manager, system_manager), colliders_map_(colliders_map), entity_handler_(entity_handler) {}

void MarionetteSystem::OnMarionetteUpdate(Entity *entity) {
  terminal_printf(50, 4, "food steps: %d", entity->Get<DurabilityComponent>()->current_multiplied_);
  auto dc = entity->Get<DurabilityComponent>();
  if (entity->Get<MovementComponent>()->direction_ != ZeroVec2 &&
      !entity->Get<RigidBodyComponent>()->AnyRigidCollisions()) {
    dc->Subtract(1);
  }
  if (dc->current_multiplied_ <= 0 || entity->Get<HPComponent>()->heal_point_ <= 0) {
    auto pcc = entity->Get<PlayerControlComponent>();
    entity_handler_->player_->Get<WalletComponent>()->moneys_ += entity->Get<WalletComponent>()->moneys_;
    entity_handler_->player_->Add<PlayerControlComponent>(pcc->right_button_, pcc->left_button_, pcc->down_button_,
                                                          pcc->up_button_, pcc->switch_food_button_,
                                                          pcc->walk_for_food_button_);
    entity_handler_->player_->Add<ActionComponent>();
    entity_handler_->player_->Add<TargetComponent>();
    entity_handler_->marionette_->Delete<MarionetteComponent>();
    entity_handler_->marionette_->Delete<PlayerControlComponent>();
    entity_handler_->marionette_->Delete<ActionComponent>();
    entity_handler_->marionette_->Delete<TargetComponent>();
    entity->Add<RemovabilityComponent>();
    entity_handler_->Update();
    GetSystemManager().Disable<MarionetteSystem>();
  }
}

void MarionetteSystem::OnUpdate() {
  LogPrint(tag_);
  if (entity_handler_->marionette_ != nullptr) {
    OnMarionetteUpdate(entity_handler_->marionette_);
  }
}
