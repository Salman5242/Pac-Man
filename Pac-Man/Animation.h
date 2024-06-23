#pragma once

#include "SFML/Graphics.hpp"

class Animation
{
private:
	sf::IntRect* bounds;
	int fps;
	sf::Clock CLK;
	int Value_reset;

public:
	void Frame_changer();
	sf::IntRect getBounds();
	Animation(sf::IntRect* rect, int NumberOframes);
};
