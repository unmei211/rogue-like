#ifndef INCLUDE_ROGUE_SYSTEMS_TAKE_MEDICINE_SYSTEM_H_
#define INCLUDE_ROGUE_SYSTEMS_TAKE_MEDICINE_SYSTEM_H_

#include <string>

#include "lib/ecs/system.h"
#include "rogue/tools/entity_handler.h"
#include "rogue/tools/entity_map.h"
class TakeMedicineSystem : public ISystem {
  EntityHandler* entity_handler_;
  EntityMap* entity_map_;
  void OnTakeMedicine(Entity* entity);

 protected:
  std::string tag_ = "TakeMedicineSystem";
  void OnUpdate() override;

 public:
  TakeMedicineSystem(EntityManager* entity_manager, SystemManager* system_manager, EntityHandler* entity_handler,
                     EntityMap* entity_map);
};

#endif  // INCLUDE_ROGUE_SYSTEMS_TAKE_MEDICINE_SYSTEM_H_
