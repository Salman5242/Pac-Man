#include "Controller.h"
#include"Controls.h"

void Controller::addState(Controls* state)
{
	states.push(state);
	states.top()->init();
}

void Controller::loop()
{
	states.top()->Iterate();
}

void Controller::render(sf::RenderWindow* window)
{
	states.top()->Render_Window(window);
}

void Controller::keyPressed(int code)
{
	states.top()->Pushed_Key(code);
}

void Controller::keyReleased(int code)
{
	states.top()->Released_Key(code);
}