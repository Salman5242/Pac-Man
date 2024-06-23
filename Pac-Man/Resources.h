#pragma once

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Directions.h"

#include <map>

class Resources
{
private:
	static sf::Texture Texture_Objects;
	static sf::Texture Maze_walls;

	static std::map<int, sf::Sprite*> sprites;
	static std::map<int, Animation> animations;

	static void loadSprite(int value, int rect1, int rect2, int animationframes);

	//while ghost are moving down
	static const int Pac_Man_Down;
	static const int Blinky_Down;
	static const int Pinky_Down;
	static const int Inky_Down;
	static const int Clyde_Down;

	//while ghost are moving left
	static const int Pac_Man_Left;
	static const int Blinky_Left;
	static const int Pinky_Left;
	static const int Clyde_Left;
	static const int Inky_Left;

	//while ghost are moving right
	static const int Blinky_Right;
	static const int Pac_Man_Right;
	static const int Pinky_Right;
	static const int Inky_Right;
	static const int Clyde_Right;

public:
	static void Draw_resources();
	static sf::Sprite* get(int value, bool animated, Direction facing);

	static sf::Sprite* Pieces_Maze[];

	//while ghost are moving up or normal
	static const int Pac_man;
	static const int Blinky_ghost1;
	static const int Pinky_ghost2;
	static const int Inky_ghost3;
	static const int Clyde_ghost4;


	static const int Ghost_frighten;
	static const int Pac_dead;

	
};
