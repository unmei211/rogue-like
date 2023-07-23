#include "lib/utils/ignore_entity.h"

bool Ignore(const Entity &entity) {
  return entity.Contains<RemovabilityComponent>() && entity.Get<RemovabilityComponent>()->must_be_deleted_;
}
