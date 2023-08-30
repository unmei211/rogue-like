#ifndef INCLUDE_ROGUE_COLORS_COLORS_H_
#define INCLUDE_ROGUE_COLORS_COLORS_H_

#include <BearLibTerminal.h>
class Colors {
 public:
  explicit Colors(color_t corner) : c1_(corner), c2_(corner), c3_(corner), c4_(corner) {}
  Colors(color_t c1, color_t c2, color_t c3, color_t c4) : c1_(c1), c2_(c2), c3_(c3), c4_(c4) {}
  Colors() = default;
  Colors(const Colors& colors) : c1_(colors.c1_), c2_(colors.c2_), c3_(colors.c3_), c4_(colors.c4_) {}
  ~Colors() = default;
  color_t c1_;
  color_t c2_;
  color_t c3_;
  color_t c4_;
  color_t corners_[4] = {c1_, c2_, c3_, c4_};

  color_t corners_almost_transporent[4] = {c1_ - 0xCC000000, c2_ - 0xCC000000, c3_ - 0xCC000000, c4_ - 0xCC000000};
  color_t corners_medium_transporent[4] = {c1_ - 0x99000000, c2_ - 0x99000000, c3_ - 0x99000000, c4_ - 0x99000000};
  Colors operator=(const Colors& colors) {
    auto temp = Colors(colors.c1_, colors.c2_, colors.c3_, colors.c4_);
    return temp;
  }
};

const Colors Blue(0xff0000ff);
const Colors Red(0xffff0000);
const Colors Transparent(0x00000000);
const Colors White(0xffffffff);
const Colors PinkEnemy(0xffff76a4);
const Colors YellowCoin(0xffE4E391);
const Colors OrangeGreenFoodMango(0xddB4C75C, 0xffDBD82E, 0xffB4C75C, 0xffDBD82E);
const Colors LightBrownGamburger(0xffDB986A);
const Colors GreenRedMedicine(0xff5BE000, 0xAAE03422, 0xff5BE000, 0xffE03422);
const Colors GreenJuice(0xff8AF071);
const Colors RedBeef(0xffFA899D);
const Colors BrownDoor(0xffDB764A);
const Colors WhiteWall(0xffEFEDCA);
const Colors PurpleBackground(0xff352C78);
const Colors GreyBackground(0xff222222);
const Colors WhiteFloorTrap(0xffffffff);

const Colors WhiteFloor(0xffffffff);
// const Colors PurpleBackground(0xff757ed9);

#endif  // INCLUDE_ROGUE_COLORS_COLORS_H_
