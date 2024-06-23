#pragma once

#include "SFML/Graphics.hpp"

class Controls
{
public:
	virtual void init() {}
	virtual void Pushed_Key(int code) = 0;
	virtual void Released_Key(int code) = 0; virtual void Iterate() = 0;
	virtual void Render_Window(sf::RenderWindow* window) = 0;
};
