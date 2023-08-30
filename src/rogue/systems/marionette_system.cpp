#include "rogue/systems/marionette_system.h"

#include "lib/ecs/system_manager.h"
#include "rogue/entity-filters/filters.h"

MarionetteSystem::MarionetteSystem(EntityManager *entity_manager, SystemManager *system_manager,
                                   EntityHandler *entity_handler, EntityMap *entity_map)
    : ISystem(entity_manager, system_manager), entity_map_(entity_map), entity_handler_(entity_handler) {}

void MarionetteSystem::OnMarionetteUpdate(Entity *entity) {
  terminal_printf(17, 1, "FOOD STEPS: %d", entity->Get<DurabilityComponent>()->current_multiplied_);
  terminal_printf(2, 2, "FOOD MONEY: %d", entity->Get<WalletComponent>()->moneys_);
  terminal_printf(69, 1, "x:%d y:%d", ToPos(entity->Get<TransformComponent>()->pos_.x_),
                  ToPos(entity->Get<TransformComponent>()->pos_.y_));
  auto dc = entity->Get<DurabilityComponent>();
  if (entity->Get<MovementComponent>()->direction_ != ZeroVec2 &&
      !entity->Get<RigidBodyComponent>()->AnyRigidCollisions()) {
    dc->Subtract(1);
  }
  if (dc->current_multiplied_ <= 0 || entity->Get<HPComponent>()->heal_point_ <= 0) {
    auto pcc = entity->Get<PlayerControlComponent>();
    entity_handler_->player_->Get<WalletComponent>()->moneys_ += entity->Get<WalletComponent>()->moneys_;
    entity_handler_->player_->Add<PlayerControlComponent>(
        pcc->right_button_, pcc->left_button_, pcc->down_button_, pcc->up_button_, pcc->switch_food_button_,
        pcc->walk_for_food_button_, pcc->use_heal_button_, pcc->throw_trap_button_);
    entity_handler_->player_->Add<ActionComponent>();
    entity_handler_->player_->Add<TargetComponent>();
    entity_handler_->player_->Add<VisionComponent>(entity_handler_->marionette_->Get<VisionComponent>()->distance_);
    entity_handler_->marionette_->Delete<VisionComponent>();
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
