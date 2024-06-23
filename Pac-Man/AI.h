#pragma once
#include "Controls.h"
#include "Maze.h"
#include "Operation.h"
#include "PacMan.h"
#include "Ghost.h"

class AI : public Controls
{

public:
	void init();
	void Iterate();
	void Render_Window(sf::RenderWindow* window);
	void Pushed_Key(int Key_Code);
	void Released_Key(int Key_Code);

private:
	Maze* maze;

	//creating objects of AI and Player

	PacMan* Pac_Obj;
	Ghost* Blinky_Obj;
	Ghost* Pinky_Obj;
	Ghost* Inky_Obj;
	Ghost* Clyde_Obj;

	int Timer;

	bool pacmanCanMove();
	bool ghostCanMove(Ghost* ghost);
	float Distance_calculate(Ghost* ghost, int addX, int addY);
	void Frightened_Ghost(Ghost* ghost);
	void Movement_Ghost(Ghost* ghost);
	void Teleporter(Operation* entity);
};
