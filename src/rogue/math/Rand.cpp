#include "rogue/math/Rand.h"

#include <ctime>
#include <random>

int Rand(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> uid(min, max);
  return uid(gen);
}
