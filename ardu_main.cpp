
#include "Arduboy.h"
#include "Game.h"



void main_setup()
{
	arduboy.begin();
	arduboy.setFrameRate(60);
	Init();
}

void main_loop()
{
	scrollBlock();
	moveSpaceCraft(craft);
	arduboy.clear();
	draw();
	arduboy.display();
}
