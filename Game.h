#ifndef __GAME_H__
#define __GAME_H__

#include "Arduboy.h"
#include "Global.h"
#include "Block.h"
#include "SpaceCraft.h"

SpaceCraft craft;

void titleInit()
{

}

void gameInit()
{
	score = 0;
	initBlock();
	arduboy.clear();
	drawBlock();
	arduboy.display();
}

void Init()
{
	gameInit();
}

void titleMain()
{

}

void gameMain()
{

}

void run() {
	gameMain();
}

void titleDraw()
{

}

void gameDraw()
{
	arduboy.drawLine(GAME_PANEL_X, 0, GAME_PANEL_X, 96, 1);
	arduboy.drawLine(SCORE_PANEL_X, 0, SCORE_PANEL_X, 96, 1);
	drawBlock();
	drawSpaceCraft(craft);

	//Drawing Score
	int tmp = score;
	for (byte i = 0; i < 5; i++) {
		arduboy.drawBitmap(SCORE_PANEL_X + 22 - i * 4, 5, bitmap_digit[tmp % 10], 3, 5, 1);
		tmp /= 10;
	}
}

void draw()
{
	gameDraw();
}

#endif // !__GAME_H__
