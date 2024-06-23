#pragma once

#include "Operation.h"

#include "Directions.h"

class Ghost : public Operation
{
private:
	int X_destination;
	int Y_destination;
	int frightened;
	

	bool Is_scattering;
	bool IsOut_cage;
	bool decide;


	Direction isMoving;
	

public:
	Ghost(int tilePosX, int tilePosY, int destinationX, int destinationY);

	void Destination_setter(int x, int y);
	int Get_X();
	int Get_Y();

	void DirectionSet(Direction dir);
	Direction directionGet();
	void Chane_Position();

	bool is_scatter();
	void scattering_setter(bool s);

	bool IsOutside_cage();

	bool Decision_taker();
	void Decision_setter(bool d);

	void Teleport(int x, int y);

	void Frightened_setter(bool f);
	bool Is_frightened();
};
