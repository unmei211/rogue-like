#include "rogue/systems/ability_control_system.h"

#include <lib/ecs/system_manager.h>

#include <vector>

#include "rogue/components/tags/manipulator_component.h"
#include "rogue/entity-filters/filters.h"
#include "rogue/systems/marionette_system.h"

AbilityControlSystem::AbilityControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                           const Controls& controls, EntityHandler* entity_handler,
                                           CollidersMap* colliders_map)
    : ISystem(entity_manager, system_manager),
      entity_handler_(entity_handler),
      colliders_map_(colliders_map),
      controls_(controls) {}

void AbilityControlSystem::CreateMarionette(Entity* entity, const Vec2& cell_pos) {
  auto stomach = entity->Get<StomachComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();

  auto food = stomach->GetFood();
  stomach->PopFood();
  food->Delete<ItemComponent>();
  food->Add<TransformComponent>(cell_pos);
  food->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  food->Add<MarionetteComponent>();
  food->Add<ActionComponent>();
  food->Add<LiftAbilityComponent>();
  food->Get<LiftAbilityComponent>()->lifted_filter_.insert(typeid(CoinComponent));
  food->Add<RigidBodyComponent>(false);
  food->Add<WalletComponent>();
  food->Add<TargetComponent>();
  food->Add<HPComponent>();
  food->Add<MovementComponent>(OnesVec2, ZeroVec2);
  food->Add<PlayerControlComponent>(pcc->right_button_, pcc->left_button_, pcc->down_button_, pcc->up_button_,
                                    pcc->switch_food_button_, pcc->walk_for_food_button_);
  colliders_map_->Put(cell_pos, food);
  entity_handler_->having_control_->Delete<PlayerControlComponent>();
  entity_handler_->having_control_->Delete<TargetComponent>();
  entity_handler_->having_control_->Delete<ActionComponent>();
  entity_handler_->having_control_ = food;
  entity_handler_->Update();
  GetSystemManager().Enable<MarionetteSystem>();
}

void AbilityControlSystem::OnUpdateEntity(Entity* entity) {
  auto pcc = entity->Get<PlayerControlComponent>();
  if (HasStomach(*entity)) {
    auto action = entity->Get<ActionComponent>();
    auto stomach = entity->Get<StomachComponent>();
    if (controls_.IsPressed(pcc->switch_food_button_)) {
      action->acted_ = true;
      stomach->Switch();
    }
    if (controls_.IsPressed(pcc->walk_for_food_button_) && entity->Contains<Manipulator>()) {
      action->acted_ = true;
      if (stomach->IsEmpty()) {
        return;
      }
      std::vector<Vec2> checker = {
          UpVec2,
          LeftVec2,
          RightVec2,
          DownVec2,
      };
      auto tc = entity->Get<TransformComponent>();
      auto ac = entity->Get<ActionComponent>();
      if (ac->old_direction_ != ZeroVec2 && colliders_map_->GetSize(tc->pos_.VecToPos() + ac->old_direction_) == 0) {
        CreateMarionette(entity, tc->pos_.VecToPos() + ac->old_direction_);
      } else {
        for (auto i : checker) {
          auto cage_pos = tc->pos_.VecToPos() + i;
          if (colliders_map_->GetSize(cage_pos) == 0) {
            CreateMarionette(entity, cage_pos);
            break;
          }
        }
      }
    }
  } else if (entity->Contains<MarionetteComponent>()) {
    if (controls_.IsPressed(pcc->walk_for_food_button_)) {
      entity_handler_->player_->Get<WalletComponent>()->moneys_ += entity->Get<WalletComponent>()->moneys_;
      entity_handler_->player_->Add<PlayerControlComponent>(pcc->right_button_, pcc->left_button_, pcc->down_button_,
                                                            pcc->up_button_, pcc->switch_food_button_,
                                                            pcc->walk_for_food_button_);
      entity_handler_->having_control_ = entity_handler_->player_;
      entity_handler_->having_control_->Add<TargetComponent>();
      entity_handler_->having_control_->Add<ActionComponent>();

      entity->Delete<MarionetteComponent>()
          ->Delete<LiftAbilityComponent>()
          ->Delete<RigidBodyComponent>()
          ->Delete<WalletComponent>()
          ->Delete<MovementComponent>()
          ->Delete<PlayerControlComponent>()
          ->Delete<HPComponent>()
          ->Delete<TargetComponent>()
          ->Add<LootComponent>()
          ->Add<TakeableComponent>();
      entity_handler_->Update();
      GetSystemManager().Disable<MarionetteSystem>();
    }
  }
}

void AbilityControlSystem::OnUpdate() {
  LogPrint(tag_);

  OnUpdateEntity(entity_handler_->having_control_);
}
