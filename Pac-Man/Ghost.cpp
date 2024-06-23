#include "Ghost.h"

Ghost::Ghost(int Pos_X, int Pos_Y, int X_destination, int Y_destination) : Operation(Pos_X, Pos_Y)
{
	Destination_setter(X_destination, Y_destination);
	DirectionSet(Direction::Unset);
	Is_scattering = true;
	IsOut_cage = false;
	decide = true;
	frightened = false;
}


int Ghost::Get_X()
{
	return X_destination;
}

int Ghost::Get_Y()
{
	return Y_destination;
}

void Ghost::DirectionSet(Direction dir)
{
	isMoving = dir;
}

void Ghost::Destination_setter(int x, int y)
{
	X_destination = x;
	Y_destination = y;
}

Direction Ghost::directionGet()
{
	return isMoving;
}

void Ghost::Chane_Position()
{
	switch (isMoving)
	{
	case Direction::Up:
		Operation::move(0, -0.1f);     //0.19f speed by vector, to move up,down,left,right
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

void Ghost::scattering_setter(bool s)
{
	Is_scattering = s;
}

bool Ghost::IsOutside_cage()
{
	return IsOut_cage;
}

bool Ghost::is_scatter()
{
	return Is_scattering;
}

bool Ghost::Decision_taker()
{
	return decide;
}

void Ghost::Decision_setter(bool d)
{
	decide = d;
}


bool Ghost::Is_frightened()
{
	if (frightened > 0) frightened--;
	return frightened > 0;
}


void Ghost::Teleport(int x, int y)
{
	Operation::Respawn(x, y);
	IsOut_cage = true;
}

void Ghost::Frightened_setter(bool f)
{
	if (f)
		frightened = 2000;
	else
		frightened = 0;
}