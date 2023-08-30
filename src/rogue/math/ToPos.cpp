#include "lib/math/to_pos.h"

int ToPos(float pos) {
  return static_cast<int>(std::round(pos));
}
