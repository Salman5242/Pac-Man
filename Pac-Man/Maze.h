#pragma once

#include "PacMan.h"
#include "Ghost.h"

class Maze
{
public:
	static const int X_Size = 28;
	static const int Y_Size = 36;

	Maze();
	int getTileCode(int x, int y);

	bool isIntersection(int x, int y);
	bool tile_Blocks_Entity(int x, int y);
	
	void removeDot(PacMan* pacman, Ghost* ghost1, Ghost* ghost2, Ghost* ghost3, Ghost* ghost4);

private:
	int tiles[X_Size][Y_Size];
	int wall;
};
