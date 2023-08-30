#include "rogue/systems/ability_control_system.h"

#include <lib/ecs/system_manager.h>

#include <vector>

#include "rogue/components/tags/manipulator_component.h"
#include "rogue/entity-filters/filters.h"
#include "rogue/systems/marionette_system.h"

AbilityControlSystem::AbilityControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                           const Controls& controls, EntityHandler* entity_handler,
                                           EntityMap* entity_map, EntityCreator* entity_creator)
    : ISystem(entity_manager, system_manager),
      entity_handler_(entity_handler),
      entity_map_(entity_map),
      entity_creator_(entity_creator),
      controls_(controls) {}

void AbilityControlSystem::CreateMarionette(Entity* entity, const Vec2& cell_pos) {
  auto stomach = entity->Get<StomachComponent>();
  auto pcc = entity->Get<PlayerControlComponent>();

  auto food = stomach->GetItem();
  stomach->PopItem();
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
  food->Add<VisionComponent>(entity_handler_->having_control_->Get<VisionComponent>()->distance_);
  food->Add<MovementComponent>(OnesVec2, ZeroVec2);
  food->Add<PlayerControlComponent>(pcc->right_button_, pcc->left_button_, pcc->down_button_, pcc->up_button_,
                                    pcc->switch_food_button_, pcc->walk_for_food_button_, pcc->use_heal_button_,
                                    pcc->throw_trap_button_);
  entity_map_->Put(cell_pos, food);
  entity_handler_->having_control_->Delete<PlayerControlComponent>();
  entity_handler_->having_control_->Delete<TargetComponent>();
  entity_handler_->having_control_->Delete<ActionComponent>();
  entity_handler_->having_control_->Delete<VisionComponent>();
  entity_handler_->having_control_ = food;
  entity_handler_->Update();
  GetSystemManager().Enable<MarionetteSystem>();
}

void AbilityControlSystem::CreateTrap(Entity* player, const Vec2& pos) {
  auto trap = GetEntityManager().CreateEntity();
  entity_creator_->CreateHandledTrap(trap, 'T', pos);
  trap->Get<TrapComponent>()->current_state_ = 2;
  entity_map_->Put(pos, trap);
  entity_handler_->traps_.insert(trap);
}

void AbilityControlSystem::OnUpdateEntity(Entity* entity) {
  auto pcc = entity->Get<PlayerControlComponent>();
  if (entity->Get<MovementComponent>()->direction_ != ZeroVec2) {
    return;
  }
  if (HasStomach(*entity)) {
    auto action = entity->Get<ActionComponent>();
    auto stomach = entity->Get<StomachComponent>();
    if (controls_.IsPressed(pcc->switch_food_button_)) {
      action->acted_ = true;
      stomach->Switch();
      return;
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
      if (ac->old_direction_ != ZeroVec2 &&
          !entity_map_->CellContains<ColliderComponent>(tc->pos_.VecToPos() + ac->old_direction_)) {
        CreateMarionette(entity, tc->pos_.VecToPos() + ac->old_direction_);
        return;
      } else {
        for (auto i : checker) {
          auto cage_pos = tc->pos_.VecToPos() + i;
          if (!entity_map_->CellContains<ColliderComponent>(cage_pos)) {
            CreateMarionette(entity, cage_pos);
            return;
          }
        }
      }
    }
  }
  if (entity->Contains<MedicineSlotComponent>()) {
    if (controls_.IsPressed(pcc->use_heal_button_)) {
      auto slot = entity->Get<MedicineSlotComponent>();
      entity->Get<ActionComponent>()->acted_ = true;
      if (slot->numbers_of_medicine_ > 0) {
        entity->Get<HPComponent>()->AddHp(25);
        slot->numbers_of_medicine_--;
      }
      return;
    }
  }

  if (HasTrapSlot(*entity)) {
    if (controls_.IsPressed(pcc->throw_trap_button_) && entity->Get<TrapsSlotComponent>()->number_of_traps > 0) {
      auto slot = entity->Get<TrapsSlotComponent>();
      if (slot->number_of_traps > 0) {
        std::vector<Vec2> checker = {
            UpVec2,
            LeftVec2,
            RightVec2,
            DownVec2,
        };
        auto tc = entity->Get<TransformComponent>();
        auto ac = entity->Get<ActionComponent>();
        if (ac->old_direction_ != ZeroVec2 &&
            !entity_map_->CellContains<ColliderComponent>(tc->pos_.VecToPos() + ac->old_direction_)) {
          CreateTrap(entity, tc->pos_.VecToPos() + ac->old_direction_);
          entity->Get<TrapsSlotComponent>()->number_of_traps -= 1;
        } else {
          for (auto i : checker) {
            auto cage_pos = tc->pos_.VecToPos() + i;
            if (!entity_map_->CellContains<ColliderComponent>(cage_pos)) {
              CreateTrap(entity, cage_pos);
              entity->Get<TrapsSlotComponent>()->number_of_traps -= 1;
              break;
            }
          }
        }
      }
      return;
    }
  }

  if (entity->Contains<MarionetteComponent>()) {
    if (controls_.IsPressed(pcc->walk_for_food_button_)) {
      entity->Get<MovementComponent>()->direction_ = ZeroVec2;
      entity_handler_->player_->Get<WalletComponent>()->moneys_ += entity->Get<WalletComponent>()->moneys_;
      entity_handler_->player_->Add<PlayerControlComponent>(
          pcc->right_button_, pcc->left_button_, pcc->down_button_, pcc->up_button_, pcc->switch_food_button_,
          pcc->walk_for_food_button_, pcc->use_heal_button_, pcc->throw_trap_button_);
      entity_handler_->having_control_ = entity_handler_->player_;
      entity_handler_->having_control_->Add<TargetComponent>();
      entity_handler_->having_control_->Add<VisionComponent>();
      entity_handler_->having_control_->Get<VisionComponent>()->distance_ = entity->Get<VisionComponent>()->distance_;
      entity_handler_->having_control_->Add<ActionComponent>();

      entity->Delete<MarionetteComponent>()
          ->Delete<LiftAbilityComponent>()
          ->Delete<RigidBodyComponent>()
          ->Delete<WalletComponent>()
          ->Delete<MovementComponent>()
          ->Delete<PlayerControlComponent>()
          ->Delete<HPComponent>()
          ->Delete<TargetComponent>()
          ->Delete<VisionComponent>()
          ->Add<LootComponent>()
          ->Add<TakeableComponent>();
      entity_handler_->Update();
      GetSystemManager().Disable<MarionetteSystem>();
      return;
    }
  }
}

void AbilityControlSystem::OnUpdate() {
  LogPrint(tag_);

  OnUpdateEntity(entity_handler_->having_control_);
}
