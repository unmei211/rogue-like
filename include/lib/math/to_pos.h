#ifndef INCLUDE_LIB_MATH_TO_POS_H_
#define INCLUDE_LIB_MATH_TO_POS_H_

#include "cmath"

int ToPos(float pos) {
  return static_cast<int>(std::round(pos));
}

#endif  // INCLUDE_LIB_MATH_TO_POS_H_
