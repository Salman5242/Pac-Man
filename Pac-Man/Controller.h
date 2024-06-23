#pragma once

#include <stack>
#include "SFML/Graphics.hpp"
#include "Controls.h"

class Controller
{
private:
	std::stack<Controls*> states;

public:
	void addState(Controls* state);
	void loop();
	void render(sf::RenderWindow* window);
	void keyPressed(int code);
	void keyReleased(int code);
};
