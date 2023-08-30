#ifndef INCLUDE_ROGUE_TOOLS_GRAPHICS_CHANGER_H_
#define INCLUDE_ROGUE_TOOLS_GRAPHICS_CHANGER_H_
#include <BearLibTerminal.h>

#include <constants.h>

class GraphicsChanger {
 public:
  static void ChangeGraphics() {
    terminal_setf("0xE005 : %s", WALL_TEXTURE_PATH);
    terminal_setf("0xE006 : %s", FLOOR_TEXTURE_PATH);
    terminal_setf("0xE007: %s", PLAYER_TEXTURE_PATH);
    terminal_setf("0xE001: %s, align=center", HAMBURGER_TEXTURE_PATH);
    terminal_setf("0xE000: %s, align=center", MANGO_TEXTURE_PATH);
    terminal_setf("0xE002: %s, align=center, resize=32x32", JUICE_TEXTURE_PATH);
    terminal_setf("0xE003: %s, align=center,resize=40x40", BEEF_TEXTURE_PATH);
    terminal_setf("0xE004: %s", ENEMY_TEXTURE_PATH);
    terminal_setf("0xE008: %s", DOOR_EXIT_TEXTURE_PATH);
    terminal_setf("0xE009: %s", DOOR_ENTER_TEXTURE_PATH);
    terminal_setf("0xE010: %s,align=center", HEAL_TEXTURE_PATH);
    terminal_setf("0xE011: %s,align=center", COIN_TEXTURE_PATH);
    terminal_setf("0xE012: %s, align=center, resize=30x35", FLOOR_TRAP_CLOSED_TEXTURE_PATH);
    terminal_setf("0xE013: %s, align=center, resize=30x35", FLOOR_TRAP_READY_TEXTURE_PATH);
    terminal_setf("0xE014: %s, align=center, resize=30x35", FLOOR_TRAP_FORWARD_TEXTURE_PATH);
    terminal_setf("0xE015: %s, align=center, resize=16x40", HANDLED_TRAP_CLOSED_TEXTURE_PATH);
    terminal_setf("0xE017: %s, align=center, resize=32x40", HANDLED_TRAP_OPEN_TEXTURE_PATH);
    terminal_setf("0xE016: %s, align=center, resize=32x40", HANDLED_TRAP_IN_ACTION_TEXTURE_PATH);
    terminal_setf("font: %s, size=32x64", FONT_PATH);
  }
};

#endif  // INCLUDE_ROGUE_TOOLS_GRAPHICS_CHANGER_H_
