#include "PacMan.h"
#include<iostream>
using namespace std;


PacMan::PacMan() : Operation(13, 26)
{
	eatenDots = 0;
}

void PacMan::queueDirection(Direction direction_obj)
{
	//using built-in queue function
	if (!directions.empty())
	{
		if (direction_obj == -directions.front())
		{
			//giving direction to pacman  

			std::queue<Direction> clear;
			std::swap(directions, clear);
		}
	}

	if (directions.size() < 2)
		directions.push(direction_obj);
}


void PacMan::eatDot()
{
	eatenDots++;
	
	if (eatenDots % 5 == 0)
	{
		system("cls");
		cout << "Score : " << (eatenDots * 3) + rand() % 30 << endl;
	}
}


std::queue<Direction> PacMan::getDirections()
{
	return directions;
}

int PacMan::getDotsEaten()
{
	return eatenDots;
}

void PacMan::set_Dead(bool d)
{
	dead = d;
}

bool PacMan::has_died()
{
	return dead;
}

void PacMan::stop()
{
	if (directions.size() > 1)
	{
		if ((int)(XPOS + 8) % 16 == 0 && (int)(YPOS + 8) % 16 == 0)
		{
			switch (directions.front()) //checking if dirctions are empty
			{
			case Direction::Up:      //using built-in function
				directions.pop();
				break;
			case Direction::Down:
				directions.pop();
				break;
			case Direction::Left:
				directions.pop();
				break;
			case Direction::Right:
				directions.pop();
				break;
			}
		}
	}
}

void PacMan::move()
{
	if (!directions.empty())
	{
		switch (directions.front())
		{
		case Direction::Up:
			Operation::move(0, -0.1f);      //0.19f speed by vector, to move up,down,left,right
			break;
		case Direction::Down:
			Operation::move(0, 0.1f);
			break;
		case Direction::Left:
			Operation::move(-0.1f, 0);
			break;
		case Direction::Right:
			Operation::move(0.1f, 0);
			break;
		}
	}
}