#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "Arduboy.h"

Arduboy arduboy;

const byte INFO_PANEL_WIDTH = 4;
const byte GAME_PANEL_WIDTH = 92;
const byte SCORE_PALEN_WIDTH = 28;

const byte INFO_PANEL_X = 0;
const byte GAME_PANEL_X = INFO_PANEL_WIDTH;
const byte SCORE_PANEL_X = GAME_PANEL_X + GAME_PANEL_WIDTH;

const byte BLOCK_SIZE = 4;
const byte CELL_DISPLAY_WIDTH = 24;// 32;
const byte CELL_DISPLAY_HEIGHT = 16;
const byte CELL_HIDE_HEIGHT = 8;
const byte CELL_ALL_HEIGHT = CELL_DISPLAY_HEIGHT + CELL_HIDE_HEIGHT;
const int16_t SCROLL_INTERVAL = 150;

const byte SPACECRAFT_Y = 58;
const byte SPACECRAFT_SPEED = 1;

byte cell[CELL_ALL_HEIGHT][CELL_DISPLAY_WIDTH / 8];

int16_t scroll_interval;
int16_t create_interval;

uint16_t score;

#endif // !__GLOBAL_H__
