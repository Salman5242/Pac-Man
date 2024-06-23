#include "Operation.h"

#include <cmath>

Operation::Operation(int tile_X, int tile_Y)
{
	tileX = tile_X;
	tileY = tile_Y;
	XPOS = tile_X * 16.0f + 8.0f + 8.0f;
	YPOS = tile_Y * 16.0f + 8.0f;
}

float Operation::PosX_screen()
{
	return XPOS;
}

float Operation::PosY_screen()
{
	return YPOS;
}

int Operation::XTile_getter()
{
	return tileX;
}

int Operation::YTile_getter()
{
	return tileY;
}

void Operation::move(float x, float y)
{
	XPOS += x;
	YPOS += y;

	if ((int)(XPOS + 8) % 16 == 0 && (int)(YPOS + 8) % 16 == 0)      // moving the entity using math function and through x,y destination
	{
		tileX = (int)round((XPOS - 8) / 16);
		tileY = (int)round((YPOS - 8) / 16);
	}
}

void Operation::Respawn(int x, int y) 
{
	tileX = x;
	tileY = y;
	XPOS = x * 16.0f + 8.0f;
	YPOS = y * 16.0f + 8.0f;
}