#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include "lib/math/vec2.h"
extern const char* TERMINAL_CFG;
extern const char* GAME_NAME;
extern const char* WIN_SCREEN_STATS_PATH;

extern const char* LEVEL1_NAME;
extern const char* LEVEL1_PATH;

extern const char* LEVEL2_NAME;
extern const char* LEVEL2_PATH;

extern const char* LEVEL3_NAME;
extern const char* LEVEL3_PATH;

extern const char* LEVEL_RANDOM_NAME;
extern const char* LEVEL_RANDOM_PATH;

extern const char* LEVEL_RANDOM_NAME_NEXT;
extern const char* LEVEL_RANDOM_NEXT_PATH;

extern const char* SCORES_DEFAULT_PATH;

extern const char* FLOOR_TRAP_CLOSED_TEXTURE_PATH;
extern const char* FLOOR_TRAP_READY_TEXTURE_PATH;
extern const char* FLOOR_TRAP_FORWARD_TEXTURE_PATH;
extern const char* HANDLED_TRAP_CLOSED_TEXTURE_PATH;
extern const char* HANDLED_TRAP_OPEN_TEXTURE_PATH;
extern const char* HANDLED_TRAP_IN_ACTION_TEXTURE_PATH;

extern const char* WALL_TEXTURE_PATH;
extern const char* FLOOR_TEXTURE_PATH;
extern const char* PLAYER_TEXTURE_PATH;
extern const char* BEEF_TEXTURE_PATH;
extern const char* HAMBURGER_TEXTURE_PATH;
extern const char* MANGO_TEXTURE_PATH;
extern const char* JUICE_TEXTURE_PATH;
extern const char* ENEMY_TEXTURE_PATH;
extern const char* DOOR_EXIT_TEXTURE_PATH;
extern const char* DOOR_ENTER_TEXTURE_PATH;
extern const char* HEAL_TEXTURE_PATH;
extern const char* COIN_TEXTURE_PATH;
extern const char* FONT_PATH;

extern const char* TITLE_CONTEXT;
extern const char* GAME_CONTEXT;
extern const char* GAME_OVER_CONTEXT;
extern const char* WIN_CONTEXT;

extern const Vec2 GAME_WINDOW_L_U;
extern const Vec2 GAME_WINDOW_R_U;
extern const Vec2 GAME_WINDOW_L_D;
extern const Vec2 GAME_WINDOW_R_D;

extern const int FLOOR_MAX_HEIGHT;
extern const int FLOOR_MAX_WIDTH;

extern const int FLOOR_MIN_HEIGHT;
extern const int FLOOR_MIN_WIDTH;

extern const int TUNNEL_MIN_LENGTH;
extern const int TUNNEL_MAX_LENGTH;

extern const char* RANDOM_MAP_TRIGGER_PATH;
extern const char* GRAPHICS_SET_TRIGGER_PATH;

extern const int CELLS_PER_FOOD;
extern const int CELLS_PER_COIN;
extern const int CELLS_PER_MEDICINE;
extern const int CELLS_PER_ENEMY;
extern const int CELLS_PER_FLOOR_TRAP;
extern const int CELLS_PER_HANDLED_TRAP;
#endif  // INCLUDE_CONSTANTS_H_
