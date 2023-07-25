#ifndef INCLUDE_ROGUE_COLORS_RED_H_
#define INCLUDE_ROGUE_COLORS_RED_H_

#include <BearLibTerminal.h>
struct Red {
 public:
  color_t c1_ = 0xffff0000;
  color_t c2_ = 0xffff0000;
  color_t c3_ = 0xffff0000;
  color_t c4_ = 0xffff0000;
  color_t corners_[4] = {c1_, c2_, c3_, c4_};
};

#endif  // INCLUDE_ROGUE_COLORS_RED_H_
