#include "rogue/systems/rendering_system.h"

#include <BearLibTerminal.h>
#include <constants.h>

#include <string>
#include <vector>

#include "lib/ecs/entity_manager.h"
#include "lib/utils/controls.h"
#include "rogue/components/attributes/color_component.h"
#include "rogue/components/attributes/texture_component.h"
#include "rogue/components/attributes/transform_component.h"
#include "rogue/entity-filters/filters.h"
#include "rogue/tools/entity_map.h"

static void state_switch(bool *state) {
  if (!*state) {
    *state = true;
  } else {
    *state = false;
  }
}

void RenderingSystem::OnLightUpdate() {
  if (floor_render) {
    for (auto &pos : default_available_pos) {
      terminal_put_ext(pos.x_, pos.y_, 0, 0, gr_as_->Get('.'), entity_handler_->floor.corners_);
    }
  }
  for (auto trap : entity_handler_->traps_) {
    auto trap_component = trap->Get<TrapComponent>();
    auto &pos = trap->Get<TransformComponent>()->pos_;
    terminal_put_ext(pos.x_, pos.y_, 0, 0, trap_component->GetAssociate(),
                     trap->Get<ColorComponent>()->color_.corners_);
  }
  for (auto &e : GetEntityManager()) {
    if (HasTransform(e) && HasTexture(e) && !IsEnemy(e) && !IsTrap(e)) {
      auto texture = e.Get<TextureComponent>();
      auto transform = e.Get<TransformComponent>();
      if (HasColor(e)) {
        terminal_put_ext(ToPos(transform->pos_.x_), ToPos(transform->pos_.y_), 0, 0, gr_as_->Get(texture->symbol_),
                         e.Get<ColorComponent>()->color_.corners_);
      } else {
        terminal_put(ToPos(transform->pos_.x_), ToPos(transform->pos_.y_), gr_as_->Get(texture->symbol_));
      }
    }
  }
  for (auto enemy : entity_handler_->enemies_) {
    auto texture = enemy->Get<TextureComponent>();
    auto transform = enemy->Get<TransformComponent>();
    terminal_put_ext(ToPos(transform->pos_.x_), ToPos(transform->pos_.y_), 0, 0, gr_as_->Get(texture->symbol_),
                     enemy->Get<ColorComponent>()->color_.corners_);
  }
}
void RenderingSystem::OnVisionUpdate() {
  for (auto &entity : entity_handler_->hud_) {
    auto pos = entity->Get<TransformComponent>()->pos_;
    terminal_put(pos.x_, pos.y_, entity->Get<TextureComponent>()->symbol_);
  }
  auto entity = entity_handler_->having_control_;
  if (entity->Get<ActionComponent>()->acted_) {
    vision_bypass_.Clean();
    vision_bypass_.Bypass(entity->Get<TransformComponent>()->pos_, entity->Get<VisionComponent>()->distance_);
  }
  for (auto &wall : vision_bypass_.walls_render_) {
    terminal_put_ext(wall.first, wall.second, 0, 0, gr_as_->Get((*game_map_)[wall.second][wall.first]),
                     (*entity_map_)
                         .GetAllOfTypeOnCell<WallComponent>(Vec2(wall.first, wall.second))
                         .front()
                         ->Get<ColorComponent>()
                         ->color_.corners_);
  }
  for (auto &cell : vision_bypass_.vision_field_) {
    if (floor_render) {
      terminal_put_ext(cell.second.pos_.x_, cell.second.pos_.y_, 0, 0, gr_as_->Get('.'),
                       entity_handler_->floor.corners_);
    }
    for (auto trap : entity_map_->GetAllOfTypeOnCell<TrapComponent>(cell.second.pos_)) {
      auto trap_component = trap->Get<TrapComponent>();
      auto &pos = trap->Get<TransformComponent>()->pos_;
      terminal_put_ext(pos.x_, pos.y_, 0, 0, trap_component->GetAssociate(),
                       trap->Get<ColorComponent>()->color_.corners_);
    }
    for (auto &render_entity : entity_map_->GetAllOnCage(cell.second.pos_)) {
      if (IsTrap(*render_entity)) {
        continue;
      }
      auto texture = render_entity->Get<TextureComponent>();
      auto transform = render_entity->Get<TransformComponent>();
      terminal_put_ext(ToPos(transform->pos_.x_), ToPos(transform->pos_.y_), 0, 0, gr_as_->Get(texture->symbol_),
                       render_entity->Get<ColorComponent>()->color_.corners_);
    }
  }
}

void RenderingSystem::OnUpdate() {
  LogPrint(tag_);
  if (controls_.IsPressed(TK_L)) {
    state_switch(&light);
  }

  if (controls_.IsPressed(TK_F) && !gr_as_->StateOnSprite()) {
    state_switch(&floor_render);
  }

  if (light) {
    OnLightUpdate();
  } else {
    OnVisionUpdate();
  }
}

void RenderingSystem::OnPreUpdate() {
  begin = std::chrono::high_resolution_clock::now();
  LogPrint(tag_ + " OnPreUpdate");
  terminal_clear();
}

void RenderingSystem::OnPostUpdate() {
  LogPrint(tag_ + " OnPostUpdate");
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = end - begin;
  fps_ = std::to_string(1.0 / duration.count()).substr(0, 3);
  terminal_printf(69, 2, "FPS: %s", fps_.c_str());
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager *const entity_manager, SystemManager *const system_manager,
                                 const std::string &level_name, EntityHandler *entity_handler,
                                 std::vector<std::vector<char>> *game_map, EntityMap *entity_map,
                                 const Controls &controls, GraphicsAssociate *gr_as)
    : ISystem(entity_manager, system_manager),
      level_name_(level_name),
      entity_handler_(entity_handler),
      game_map_(game_map),
      vision_bypass_(VisionBypass(game_map)),
      entity_map_(entity_map),
      gr_as_(gr_as),
      controls_(controls) {
  vision_bypass_.Bypass(entity_handler->having_control_->Get<TransformComponent>()->pos_,
                        entity_handler->having_control_->Get<VisionComponent>()->distance_);
  if (level_name_ == LEVEL_RANDOM_NAME) {
    light = false;
    floor_render = true;
  } else {
    MapBypass bypass;
    bypass.SetMap(game_map);
    bypass.Bypass(entity_handler->player_->Get<TransformComponent>()->pos_);
    default_available_pos = bypass.GetAllAvailablePos();
  }
}
