#ifndef INCLUDE_ROGUE_SCENES_TITLE_SCENE_H_
#define INCLUDE_ROGUE_SCENES_TITLE_SCENE_H_

#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"

class TitleScene : public IScene {
  const Controls& controls_;
  bool random_trigger = false;
  bool graphics_trigger = false;

 public:
  TitleScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_TITLE_SCENE_H_
