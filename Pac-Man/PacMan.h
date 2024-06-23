#pragma once

#include "Operation.h"

#include <queue>
#include "Directions.h"

class PacMan : public Operation
{
private:
	std::queue<Direction> directions;
	int eatenDots;
	bool dead;

public:
	PacMan();

	void queueDirection(Direction dir);
	std::queue<Direction> getDirections();


	void stop();
	void move();

	void eatDot();
	int getDotsEaten();


	void set_Dead(bool d);
	bool has_died();
};
