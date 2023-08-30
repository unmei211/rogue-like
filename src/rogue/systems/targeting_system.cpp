#include "rogue/systems/targeting_system.h"

#include <queue>
#include <vector>

#include "lib/ecs/system_manager.h"
#include "rogue/systems/enemy_vision_system.h"
TargetingSystem::TargetingSystem(EntityManager *entity_manager, SystemManager *system_manager, EntityMap *entity_map,
                                 EntityHandler *entity_handler)
    : ISystem(entity_manager, system_manager), entity_map_(entity_map), entity_handler_(entity_handler) {}

bool TargetingSystem::Next(std::queue<Vertex *> *queue, const Vec2 &target_pos) {
  if (queue->empty()) {
    return false;
  }

  Vertex *current = queue->front();
  queue->pop();

  if (current->vec_ == target_pos) {
    return false;
  }

  std::vector<Vertex *> neighbors = FindNeighbors(*current);

  for (auto looking_at : neighbors) {
    if (!looking_at->visited_) {
      queue->push(looking_at);
      looking_at->visited_ = true;
      looking_at->from_ = current;
    }
  }

  return true;
}

std::vector<Vertex *> TargetingSystem::BackPath(Vec2 *target_pos) {
  Vertex *current = &map_vertices_[target_pos->GetPosPair()];
  bool done = false;
  std::vector<Vertex *> path;
  if (current->from_ == nullptr) {
    return path;
  }
  while (!done) {
    path.push_back(current);
    Vertex *previous = current->from_;

    if (previous->from_ == nullptr) {
      done = true;
    } else {
      current = previous;
    }
  }
  return path;
}

void TargetingSystem::BreadthSearch(Entity *enemy, Entity *target) {
  std::queue<Vertex *> queue;
  auto enemy_pos = enemy->Get<TransformComponent>()->pos_;
  map_vertices_[enemy_pos.GetPosPair()] = Vertex(enemy_pos);
  map_vertices_[enemy_pos.GetPosPair()].from_ = nullptr;
  map_vertices_[enemy_pos.GetPosPair()].visited_ = true;
  queue.push(&map_vertices_[enemy_pos.GetPosPair()]);

  auto target_pos = target->Get<TransformComponent>()->pos_;
  while (Next(&queue, target_pos)) {
  }
  std::vector<Vertex *> back_path = BackPath(&target_pos);
  if (back_path.empty()) {
    return;
  }
  if (entity_map_->CellContains<EnemyComponent>(back_path.back()->from_->vec_)) {
    auto direction = back_path.back()->vec_ - back_path.back()->from_->vec_;
    enemy->Get<MovementComponent>()->direction_ = direction;
    if (target->Get<TransformComponent>()->pos_.Distance(enemy->Get<TransformComponent>()->pos_.VecToPos()) <= 1) {
      enemy->Get<MovementComponent>()->direction_ = ZeroVec2;
    }
  }
}

std::vector<Vertex *> TargetingSystem::FindNeighbors(const Vertex &vertex) {
  auto hc_dir = entity_handler_->having_control_->Get<MovementComponent>()->direction_;
  std::vector<Vertex> candidates;
  if (hc_dir == ZeroVec2 || hc_dir == UpVec2 || hc_dir == DownVec2) {
    candidates = {Vertex(Vec2(vertex.vec_.x_, vertex.vec_.y_ + 1)), Vertex(Vec2(vertex.vec_.x_, vertex.vec_.y_ - 1)),
                  Vertex(Vec2(vertex.vec_.x_ + 1, vertex.vec_.y_)), Vertex(Vec2(vertex.vec_.x_ - 1, vertex.vec_.y_))};
  } else {
    candidates = {Vertex(Vec2(vertex.vec_.x_ + 1, vertex.vec_.y_)), Vertex(Vec2(vertex.vec_.x_ - 1, vertex.vec_.y_)),
                  Vertex(Vec2(vertex.vec_.x_, vertex.vec_.y_ + 1)), Vertex(Vec2(vertex.vec_.x_, vertex.vec_.y_ - 1))};
  }

  std::vector<Vertex *> result;
  auto map_size = entity_map_->GetMapSize();
  for (auto &candidate : candidates) {
    if (candidate.vec_.x_ >= 1 && candidate.vec_.y_ >= 1 && candidate.vec_.x_ < map_size.first &&
        candidate.vec_.y_ < map_size.second) {
      bool enter = true;
      for (auto entity : entity_map_->GetAllOnCage(candidate.vec_)) {
        if (entity->Contains<RigidBodyComponent>() && entity->Get<RigidBodyComponent>()->is_rigid_) {
          enter = false;
        }
      }
      if (enter) {
        if (map_vertices_.count(candidate.vec_.GetPosPair()) <= 0) {
          map_vertices_[candidate.vec_.GetPosPair()] = candidate;
        }
        result.push_back(&map_vertices_[candidate.vec_.GetPosPair()]);
      }
    }
  }
  return result;
}

void TargetingSystem::OnUpdate() {
  LogPrint(tag_);
  auto target = entity_handler_->target_;
  for (auto enemy : entity_handler_->enemies_) {
    if (ToPos(target->Get<TransformComponent>()->pos_.Distance(enemy->Get<TransformComponent>()->pos_.VecToPos())) <=
        enemy->Get<VisionComponent>()->distance_) {
      BreadthSearch(enemy, target);
    }
    map_vertices_.clear();
  }
  GetSystemManager().Disable<TargetingSystem>();
}
