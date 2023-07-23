#include "rogue/systems/rendering_system.h"

#include <BearLibTerminal.h>

#include "lib/ecs/entity_manager.h"
#include "rogue/components/texture_component.h"
#include "rogue/components/transform_component.h"

void RenderingSystem::OnUpdate() {
  LogPrint(tag_);
  for (auto &e : GetEntityManager()) {
    if (e.Contains<TransformComponent>() && e.Contains<TextureComponent>()) {
      auto texture = e.Get<TextureComponent>();
      auto transform = e.Get<TransformComponent>();

      terminal_put(ToPos(transform->pos_.x_), ToPos(transform->pos_.y_), texture->symbol_);
    }
  }
}

void RenderingSystem::OnPreUpdate() {
  LogPrint(tag_);
  terminal_clear();
}

void RenderingSystem::OnPostUpdate() {
  LogPrint(tag_);
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager *const entity_manager, SystemManager *const system_manager)
    : ISystem(entity_manager, system_manager) {}
