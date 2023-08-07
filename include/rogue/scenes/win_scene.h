#ifndef INCLUDE_ROGUE_SCENES_WIN_SCENE_H_
#define INCLUDE_ROGUE_SCENES_WIN_SCENE_H_

#include <string>
#include <vector>

#include "lib/scenes/i_scene.h"
#include "lib/utils/controls.h"

class WinScene : public IScene {
  const Controls& controls_;
  std::vector<std::string> stats;

 public:
  WinScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_ROGUE_SCENES_WIN_SCENE_H_
