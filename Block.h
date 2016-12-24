#ifndef __BLOCK_H__
#define	__BLOCK_H__

#include "Global.h"
#include "bitmaps.h"


byte getCell(byte x, byte y) {
	if (x < 0 || x >= CELL_DISPLAY_WIDTH || y < 0 || y >= CELL_ALL_HEIGHT) {
		return 0;
	}

	byte x_i = x / 8;
	 byte x_p = x % 8;

	return ((cell[y][x_i] >> x_p) & 1);
}

void setCell(byte x, byte y, byte value) {
	if (x < 0 || x >= CELL_DISPLAY_WIDTH || y < 0 || y >= CELL_ALL_HEIGHT) {
		return ;
	}

	byte x_i = x / 8;
	byte x_p = x % 8;
	
	if (value == 1) {
		cell[y][x_i] |= 1 << x_p;
	}
	else {
		cell[y][x_i] &= ~(1 << x_p);
	}
}

void initBlock()
{
	for (byte i = 0; i < CELL_DISPLAY_HEIGHT; i++) {
		for (byte j = 0; j < CELL_DISPLAY_WIDTH; j++) {
			setCell(j, i, 0);
		}
	}
	scroll_interval = SCROLL_INTERVAL;
	create_interval = 0;
}


void setBlock()
{
	byte type =  random(0, 3);

	switch (type) {
	case 0: {
		byte width = random(3, 8);
		byte height = random(1, 3);
		byte x = random(0, CELL_DISPLAY_WIDTH - width);
		for (byte i = 0; i < width; i++) {
			setCell(i + x, 0, 1);
		}
		if (random(0, 2) == 0) {
			for (byte y = 0; y < height; y++) {
				setCell(x, y + 1, 1);
			}
		}
		else {
			for (byte y = 0; y < height; y++) {
				setCell(x + width - 1, y + 1, 1);
			}
		}
	}
		break;
	case 1: {
		byte width = random(3, 8);
		byte height = random(1, 3);
		byte x = random(0, CELL_DISPLAY_WIDTH - width);
		byte pos = random(1, width - 1);
		for (byte i = 0; i < width; i++) {
			setCell(i + x, 0, 1);
		}
		for (byte y = 0; y < height; y++) {
			setCell(x + pos, y + 1, 1);
		}
	}
		break;
	case 2:
		byte width = random(4, 7);
		byte height = 3;
		byte x = random(0, CELL_DISPLAY_WIDTH - width);
		for (byte i = 0; i < width; i++) {
			setCell(i + x, 0, 1);
		}
		for (byte y = 0; y < height; y++) {
			setCell(x, y + 1, 1);
			setCell(x + width - 1, y + 1, 1);
		}
		break;
	}

	//byte width = random(5, 12);
	//byte height = random(3, 5);
	//byte lack = 5;// random(3, (width * height) / 5 + 1);
	//byte x = random(0, CELL_DISPLAY_WIDTH - width);
	//byte y = 0;

	//for (byte i = 0; i < width; i++) {
	//	for (byte j = 0; j < height; j++) {
	//		setCell(i + x, j, 1);
	//	}
	//}
	//for (byte i = 0; i < lack; i++) {
	//	byte p = random(0, width);
	//	for (byte j = height - 1; j > 0; j--) {
	//		if (getCell(p + x, j) == 1) {
	//			setCell(p + x, j, 0);
	//			break;
	//		}
	//	}
	//}
}

void createBlock()
{
	for(byte i = 0; i < 2; i++)
		setBlock();
}

void eraseBlock(byte _x, byte _y)
{
	if(getCell(_x, _y) == 0) return;

	byte left, right, top, bottom;
	left = right = _x;
	top = bottom = _y;
	while (getCell(left - 1, top) != 0) {
		if (left < 0) {
			break;
		}
		left--;
	}
	while (getCell(right, top) != 0) {
		if (right >= CELL_DISPLAY_WIDTH) {
			break;
		}
		right++;
	}
	while (getCell(left, top - 1) != 0) {
		if (top < 0) {
			break;
		}
		top--;
	}
	while (getCell(left, bottom) != 0) {
		if (bottom >= CELL_ALL_HEIGHT) {
			break;
		}
		bottom++;
	}
	byte x, y;
	for (y = top; y < bottom; y++) {
		for (x = left; x < right; x++) {
			if (getCell(x, y) != 1) {
				break;
			}
		}
		if (x < right) {
			break;
		}
	}
	if (x == right && y == bottom) {
		for (x = left; x < right; x++) {
			if (getCell(x, top - 1) != 0 || getCell(x, bottom) != 0) {
				break;
			}
		}
		for (y = top; y < bottom; y++) {
			if (getCell(left - 1, y) != 0 || getCell(right, y) != 0) {
				break;
			}
		}
		if (x == right && y == bottom) {
			for (x = left; x < right; x++) {
				for (y = top; y < bottom; y++) {
					arduboy.fillRect(x * BLOCK_SIZE, (y - CELL_HIDE_HEIGHT) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0);
					arduboy.display();
					delay(100);
					setCell(x, y, 0);
					score++;
				}
			}

		}
	}
}

void eraseBlockAll()
{
	byte left, right, top, bottom;
	for (byte i = 0; i < CELL_ALL_HEIGHT; i++) {
		for (byte j = 0; j < CELL_DISPLAY_WIDTH; j++) {
			if (getCell(j, i) == 1) {
				left = right = j;
				top = bottom = i;
				while (getCell(right, top) != 0) {
					if (right >= CELL_DISPLAY_WIDTH) {
						break;
					}
					right++;
				}
				while (getCell(left, bottom) != 0) {
					if (bottom >= CELL_ALL_HEIGHT) {
						break;
					}
					bottom++;
				}
				byte x, y;
				for (y = top; y < bottom; y++) {
					for (x = left; x < right; x++) {
						if (getCell(x, y) != 1) {
							break;
						}
					}
					if (x < right) {
						break;
					}
				}
				if (x == right && y == bottom) {
					for (x = left; x < right; x++) {
						if (getCell(x, top - 1) != 0 || getCell(x, bottom) != 0) {
							break;
						}
					}
					for (y = top; y < bottom; y++) {
						if (getCell(left - 1, y) != 0 || getCell(right, y) != 0) {
							break;
						}
					}
					if (x == right && y == bottom) {
						for (x = left; x < right; x++) {
							for (y = top; y < bottom; y++) {
								arduboy.fillRect(x * BLOCK_SIZE, (y - CELL_HIDE_HEIGHT) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0);
								arduboy.display();
								delay(100);
								setCell(x, y, 0);
							}
						}

					}
				}
			}
		}
	}
}

void scrollBlock()
{
	if (scroll_interval-- > 0) {
		return;
	}
	scroll_interval = SCROLL_INTERVAL;

	if (create_interval-- <= 0) {
		createBlock();
		create_interval = 10;
	}

	for (byte y = CELL_ALL_HEIGHT - 1; y > 0; y--) {
		for(byte x = 0; x < CELL_DISPLAY_WIDTH; x++){
			setCell(x, y, getCell(x, y - 1));
		}
	}

	for (byte x = 0; x < CELL_DISPLAY_WIDTH; x++) {
		setCell(x, 0, 0);
	}
}


void drawBlock()
{
	for (byte i = 0; i < CELL_DISPLAY_HEIGHT; i++) {
		for (byte j = 0; j < CELL_DISPLAY_WIDTH; j++) {
			if (getCell(j, i + CELL_HIDE_HEIGHT) == 1) {
				arduboy.drawRect(GAME_PANEL_X + j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 1);
			}
		}
	}

}

#endif // !___BLOCK_H__
