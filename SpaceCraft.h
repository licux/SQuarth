#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__

#include "Global.h"
#include "bitmaps.h"

struct CraftBlock
{
	int8_t cell_x;
	int8_t y;
};

struct SpaceCraft
{
	int8_t x;
	byte key_interval;
	uint16_t shot_intercal;
	CraftBlock block;
	byte status;
};



void initSpaceCraft(SpaceCraft& craft)
{
	craft.x = 3;
	craft.key_interval = 0;
	craft.shot_intercal = 0;
}

//	type 0: PLUS
//  type 1: MINUS
void shotSpaceCraft(SpaceCraft& craft, byte type)
{
	craft.block.cell_x = craft.x;
	craft.block.y = SPACECRAFT_Y;
	craft.status |= 0b00000001;

	if (type == 1) { // if minus shot
		craft.status |= 0b00000010;
	}



	byte x = craft.x;
	//byte y = CELL_ALL_HEIGHT;
	//for (; y > 0; y--) {
	//	if (getCell(x, y - 1) == 1) {
	//		setCell(x, y, 1);
	//		break;
	//	}
	//}
}

bool moveCraftBlock(SpaceCraft& craft)                                                                                                                                                         
{
	bool flag = false;
	if (getCell(craft.block.cell_x, (craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT) == 0) {
		craft.block.y -= SPACECRAFT_SPEED;
		if (craft.block.y < 0) {
			flag = true;
		}
	}
	else {
		if ((craft.status & 0b00000010) != 0b00000010) {
			setCell(craft.block.cell_x, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT) + 1, 1);
			eraseBlock(craft.block.cell_x, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT) + 1);
		}
		else {
			setCell(craft.block.cell_x, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT), 0);
			eraseBlock(craft.block.cell_x, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT) - 1);
			eraseBlock(craft.block.cell_x - 1, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT));
			eraseBlock(craft.block.cell_x + 1, ((craft.block.y - SPACECRAFT_SPEED) / BLOCK_SIZE + CELL_HIDE_HEIGHT));			
		}

		flag = true;
	}

	return flag;
}

void moveSpaceCraft(SpaceCraft& craft)
{
	// move my block
	if ((craft.status & 0b00000001) == 0b00000001) {
		if (moveCraftBlock(craft)) {
			craft.status &= ~(0b00000011);
		}
	}

	// move SpaceCraft
	if (arduboy.pressed(LEFT_BUTTON)) {
		if (craft.key_interval > 0) {
			craft.key_interval--;
		}
		else {
			craft.x -= 1;
			craft.key_interval = 30;
			if (craft.x < 0) craft.x = 0;
		}

	}else if (arduboy.pressed(RIGHT_BUTTON)) {
		if (craft.key_interval > 0) {
			craft.key_interval--;
		}
		else {
			craft.x += 1;
			craft.key_interval =30;
			if (craft.x >= CELL_DISPLAY_WIDTH) craft.x = CELL_DISPLAY_WIDTH - 1;
		}

	}
	else {
		craft.key_interval = 0;
	}

	// Shot Block
	if (arduboy.pressed(A_BUTTON + UP_BUTTON) | arduboy.pressed(B_BUTTON + UP_BUTTON))
	 {
		if (craft.shot_intercal > 0 || (craft.status & 0b00000001) == 0b00000001) {
			craft.shot_intercal--;
		}
		else {
			shotSpaceCraft(craft, 1);
			craft.shot_intercal = 500;
		}
	}
	else if (arduboy.pressed(A_BUTTON) | arduboy.pressed(B_BUTTON)) {
		if (craft.shot_intercal > 0 || (craft.status & 0b00000001) == 0b00000001) {
			craft.shot_intercal--;
		}
		else {
			shotSpaceCraft(craft, 0);
			craft.shot_intercal = 500;
		}
	}
	else {
		craft.shot_intercal = 0;
	}

}

void drawSpaceCraft(SpaceCraft& craft)
{
	if ((craft.status & 0b00000001) == 0b00000001) {
		arduboy.drawRect(GAME_PANEL_X + craft.block.cell_x * BLOCK_SIZE, craft.block.y, BLOCK_SIZE, BLOCK_SIZE, 1);
	}

	int8_t y = CELL_DISPLAY_HEIGHT;
	for (; y >= 0; y--) {
		if (getCell(craft.x, y - 1 + CELL_HIDE_HEIGHT) == 1) {
			break;
		}
	}

	arduboy.fillRect(GAME_PANEL_X + craft.x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 1);
	arduboy.drawBitmap(GAME_PANEL_X + craft.x * BLOCK_SIZE, 58, bitmap_spacecraft, 6, 6, 1);
}

#endif // !__SPACECRAFT_H__
