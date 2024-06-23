#pragma once

class Operation
{
protected:
	float XPOS;
	float YPOS;
	int tileX;
	int tileY;

public:
	Operation(int tilePosX, int tilePosY);

	float PosX_screen();
	float PosY_screen();
	int XTile_getter();
	int YTile_getter();

	void move(float x, float y);
	void Respawn(int x, int y);
};
