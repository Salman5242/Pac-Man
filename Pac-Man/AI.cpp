#include "AI.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "PacMan.h"
#include "Directions.h"
#include "Ghost.h"
#include <cmath>
#include <random>
#include <cstdlib>

using namespace sf;

void AI::init()
{

	maze = new Maze();

	Pac_Obj = new PacMan();
	Blinky_Obj = new Ghost(13, 14, 3, 4);
	Pinky_Obj = new Ghost(13, 17, 23, 4);
	Inky_Obj = new Ghost(11, 17, 26, 32);
	Clyde_Obj = new Ghost(15, 17, 1, 32);

	Blinky_Obj->Teleport(13, 14);

	srand(time(NULL));

	Timer = 0;
}

void AI::Iterate()
{
	if (pacmanCanMove() && !(Pac_Obj->has_died()))
		Pac_Obj->move();
	else
		Pac_Obj->stop();

	if (maze->isIntersection(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter()))
		Pac_Obj->stop();

	maze->removeDot(Pac_Obj, Blinky_Obj, Pinky_Obj, Inky_Obj, Clyde_Obj);

	if (!Pac_Obj->getDirections().empty())
	{
		if (!Blinky_Obj->is_scatter())
			Blinky_Obj->Destination_setter(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter());

		if (!Pinky_Obj->is_scatter())
		{
			switch (Pac_Obj->getDirections().front())
			{
			case Direction::Up:
				Pinky_Obj->Destination_setter(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter() - 4);
				break;
			case Direction::Down:
				Pinky_Obj->Destination_setter(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter() + 4);
				break;
			case Direction::Left:
				Pinky_Obj->Destination_setter(Pac_Obj->XTile_getter() - 4, Pac_Obj->YTile_getter());
				break;
			case Direction::Right:
				Pinky_Obj->Destination_setter(Pac_Obj->XTile_getter() + 4, Pac_Obj->YTile_getter());
				break;
			}
		}

		if (!Inky_Obj->is_scatter())
			Inky_Obj->Destination_setter(Pac_Obj->XTile_getter() + (Blinky_Obj->XTile_getter() - Pac_Obj->XTile_getter()), Pac_Obj->YTile_getter() + (Blinky_Obj->YTile_getter() - Pac_Obj->YTile_getter()));

		if (!Clyde_Obj->is_scatter())
		{
			if (sqrt(pow((Clyde_Obj->XTile_getter() - (Pac_Obj->XTile_getter())), 2) + pow((Clyde_Obj->YTile_getter() - (Pac_Obj->YTile_getter())), 2)) < 9)
			{
				Clyde_Obj->Destination_setter(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter());
			}
			else
			{
				Clyde_Obj->Destination_setter(1, 32);
			}
		}
	}

	Movement_Ghost(Blinky_Obj);
	Movement_Ghost(Pinky_Obj);
	Movement_Ghost(Inky_Obj);
	Movement_Ghost(Clyde_Obj);

	if (Pac_Obj->getDotsEaten() == 5)
		Pinky_Obj->Teleport(13, 14);
	if (Pac_Obj->getDotsEaten() == 50)
		Inky_Obj->Teleport(13, 14);
	if (Pac_Obj->getDotsEaten() == 100)
		Clyde_Obj->Teleport(13, 14);

	Teleporter(Pac_Obj);
	Teleporter(Blinky_Obj);
	Teleporter(Pinky_Obj);
	Teleporter(Inky_Obj);
	Teleporter(Clyde_Obj);

	Frightened_Ghost(Blinky_Obj);
	Frightened_Ghost(Pinky_Obj);
	Frightened_Ghost(Inky_Obj);
	Frightened_Ghost(Clyde_Obj);

	if (Pac_Obj->getDotsEaten() == 240)
	{
		Blinky_Obj->Teleport(-2, -2);
		Pinky_Obj->Teleport(-2, -2);
		Inky_Obj->Teleport(-2, -2);
		Clyde_Obj->Teleport(-2, -2);
		Timer++;
	}

	if (Pac_Obj->has_died())
		Timer++;

	if (Timer == 200)
	{
		if (Pac_Obj->has_died())
		{
			if (Blinky_Obj->IsOutside_cage()) Blinky_Obj->Teleport(13, 14);
			if (Pinky_Obj->IsOutside_cage()) Pinky_Obj->Teleport(13, 14);
			if (Inky_Obj->IsOutside_cage()) Inky_Obj->Teleport(13, 14);
			if (Clyde_Obj->IsOutside_cage()) Clyde_Obj->Teleport(13, 14);
			Pac_Obj->Respawn(13, 26);
			Pac_Obj->set_Dead(false);
			Timer = 0;
		}
		else
		{
			AI::init();
			Timer = 0;
		}
	}
}

void AI::Render_Window(RenderWindow* _window)
{
	Sprite pacman_Sprite;
	Sprite blinky_Sprite;
	Sprite pinky_Sprite;
	Sprite inky_Sprite;
	Sprite clyde_Sprite;

	if (Pac_Obj->getDirections().empty())
		pacman_Sprite = *Resources::get(Resources::Pac_man, false, Direction::Unset);
	else
		pacman_Sprite = *Resources::get(Resources::Pac_man, true, Pac_Obj->getDirections().front());

	if (Pac_Obj->has_died())
		pacman_Sprite = *Resources::get(Resources::Pac_dead, true, Direction::Unset);

	if (!Blinky_Obj->Is_frightened())
		blinky_Sprite = *Resources::get(Resources::Blinky_ghost1, Blinky_Obj->IsOutside_cage(), Blinky_Obj->directionGet());
	else
		blinky_Sprite = *Resources::get(Resources::Ghost_frighten, Blinky_Obj->IsOutside_cage(), Blinky_Obj->directionGet());

	if (!Pinky_Obj->Is_frightened())
		pinky_Sprite = *Resources::get(Resources::Pinky_ghost2, Pinky_Obj->IsOutside_cage(), Pinky_Obj->directionGet());
	else
		pinky_Sprite = *Resources::get(Resources::Ghost_frighten, Pinky_Obj->IsOutside_cage(), Pinky_Obj->directionGet());

	if (!Inky_Obj->Is_frightened())
		inky_Sprite = *Resources::get(Resources::Inky_ghost3, Inky_Obj->IsOutside_cage(), Inky_Obj->directionGet());
	else
		inky_Sprite = *Resources::get(Resources::Ghost_frighten, Inky_Obj->IsOutside_cage(), Inky_Obj->directionGet());

	if (!Clyde_Obj->Is_frightened())
		clyde_Sprite = *Resources::get(Resources::Clyde_ghost4, Clyde_Obj->IsOutside_cage(), Clyde_Obj->directionGet());
	else
		clyde_Sprite = *Resources::get(Resources::Ghost_frighten, Clyde_Obj->IsOutside_cage(), Clyde_Obj->directionGet());

	pacman_Sprite.setPosition(Pac_Obj->PosX_screen(), Pac_Obj->PosY_screen());
	blinky_Sprite.setPosition(Blinky_Obj->PosX_screen(), Blinky_Obj->PosY_screen());
	pinky_Sprite.setPosition(Pinky_Obj->PosX_screen(), Pinky_Obj->PosY_screen());
	inky_Sprite.setPosition(Inky_Obj->PosX_screen(), Inky_Obj->PosY_screen());
	clyde_Sprite.setPosition(Clyde_Obj->PosX_screen(), Clyde_Obj->PosY_screen());

	for (int i = 0; i < Maze::X_Size; i++)
	{
		for (int j = 0; j < Maze::Y_Size; j++)
		{
			Resources::Pieces_Maze[maze->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
			_window->draw(*Resources::Pieces_Maze[maze->getTileCode(i, j)]);
		}
	}

	_window->draw(pacman_Sprite);
	_window->draw(blinky_Sprite);
	_window->draw(pinky_Sprite);
	_window->draw(inky_Sprite);
	_window->draw(clyde_Sprite);
}

void AI::Pushed_Key(int Key_code)
{
	switch (Key_code)
	{
	case Keyboard::Up:
		Pac_Obj->queueDirection(Direction::Up);
		break;
	case Keyboard::Down:
		Pac_Obj->queueDirection(Direction::Down);
		break;
	case Keyboard::Left:
		Pac_Obj->queueDirection(Direction::Left);
		break;
	case Keyboard::Right:
		Pac_Obj->queueDirection(Direction::Right);
		break;
	}
}

void AI::Released_Key(int Key_Code)
{
}

bool AI::pacmanCanMove()
{
	if (!Pac_Obj->getDirections().empty())
	{
		switch (Pac_Obj->getDirections().front())   //tomove pacman in maze
		{
		case Direction::Up:
			return !maze->tile_Blocks_Entity(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter() - 1);  //for moving up
			break;
		case Direction::Down:
			return !maze->tile_Blocks_Entity(Pac_Obj->XTile_getter(), Pac_Obj->YTile_getter() + 1);   //for moving down
			break;
		case Direction::Left:
			return !maze->tile_Blocks_Entity(Pac_Obj->XTile_getter() - 1, Pac_Obj->YTile_getter());    //for moving left
			break;
		case Direction::Right:
			return !maze->tile_Blocks_Entity(Pac_Obj->XTile_getter() + 1, Pac_Obj->YTile_getter());      //for moving right
			break;
		}
	}
	return true;
}

void AI::Movement_Ghost(Ghost* ghost)
{
	if (ghost->is_scatter())
	{
		if (ghost->XTile_getter() == ghost->Get_X() && ghost->YTile_getter() == ghost->Get_Y())
		{
			ghost->scattering_setter(false);
		}
	}

	if (maze->isIntersection(ghost->XTile_getter(), ghost->YTile_getter()))
	{
		if (ghost->Decision_taker())
		{
			float dRight = Distance_calculate(ghost, 1, 0);
			float dLeft = Distance_calculate(ghost, -1, 0);
			float dUp = Distance_calculate(ghost, 0, -1);
			float dDown = Distance_calculate(ghost, 0, 1);

			if (dRight < dLeft && dRight < dUp && dRight < dDown)
				ghost->DirectionSet(Direction::Right);
			else if (dLeft < dRight && dLeft < dUp && dLeft < dDown)
				ghost->DirectionSet(Direction::Left);
			else if (dUp < dLeft && dUp < dRight && dUp < dDown)
				ghost->DirectionSet(Direction::Up);
			else if (dDown < dLeft && dDown < dUp && dDown < dRight)
				ghost->DirectionSet(Direction::Down);
		}
		ghost->Decision_setter(false);
	}
	else
	{
		ghost->Decision_setter(true);
	}
	if (ghostCanMove(ghost) && ghost->IsOutside_cage())
		ghost->Chane_Position();
	else
		ghost->Decision_setter(true);
}

bool AI::ghostCanMove(Ghost* ghost)
{
	switch (ghost->directionGet())
	{
	case Direction::Up:
		return !maze->tile_Blocks_Entity(ghost->XTile_getter(), ghost->YTile_getter() - 1);
		break;
	case Direction::Down:
		return !maze->tile_Blocks_Entity(ghost->XTile_getter(), ghost->YTile_getter() + 1);
		break;
	case Direction::Left:
		return !maze->tile_Blocks_Entity(ghost->XTile_getter() - 1, ghost->YTile_getter());
		break;
	case Direction::Right:
		return !maze->tile_Blocks_Entity(ghost->XTile_getter() + 1, ghost->YTile_getter());
		break;
	default:
		return false;
	}
}

float AI::Distance_calculate(Ghost* ghost, int X_add, int Y_add)
{
	float distance = 1000000.0f;
	if (!maze->tile_Blocks_Entity(ghost->XTile_getter() + X_add, ghost->YTile_getter() + Y_add))
	{
		distance = (float)sqrt(pow((ghost->Get_X() - (ghost->XTile_getter() + X_add)), 2) + pow((ghost->Get_Y() - (ghost->YTile_getter() + Y_add)), 2));
	}
	return distance;
}

void AI::Teleporter(Operation* Body)
{
	if (Body->XTile_getter() == 0 && Body->YTile_getter() == 17)
		Body->Respawn(26, 17);
	else if (Body->XTile_getter() == 27 && Body->YTile_getter() == 17)
		Body->Respawn(1, 17);
}

void AI::Frightened_Ghost(Ghost* _ghost)
{
	if (Pac_Obj->XTile_getter() == _ghost->XTile_getter() && Pac_Obj->YTile_getter() == _ghost->YTile_getter())
	{
		if (_ghost->Is_frightened())
		{
			_ghost->Teleport(13, 14);
			_ghost->Frightened_setter(false);
		}
		else
		{
			Pac_Obj->set_Dead(true);
			Blinky_Obj->Teleport(-2, -2);
			Pinky_Obj->Teleport(-2, -2);
			Inky_Obj->Teleport(-2, -2);
			Clyde_Obj->Teleport(-2, -2);
		}
	}
}