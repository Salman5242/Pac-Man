#include "Resources.h"

std::map<int, sf::Sprite*> Resources::sprites;
std::map<int, Animation> Resources::animations;

sf::Texture Resources::Texture_Objects;
sf::Texture Resources::Maze_walls;


sf::Sprite* Resources::Pieces_Maze[32];

const int Resources::Pac_man = 0;
const int Resources::Pac_Man_Down = 1;
const int Resources::Pac_Man_Left = 2;
const int Resources::Pac_Man_Right = 3;


const int Resources::Blinky_ghost1 = 4;
const int Resources::Blinky_Down = 5;
const int Resources::Blinky_Left = 6;
const int Resources::Blinky_Right = 7;


const int Resources::Pinky_ghost2 = 8;
const int Resources::Pinky_Down = 9;
const int Resources::Pinky_Left = 10;
const int Resources::Pinky_Right = 11;


const int Resources::Inky_ghost3 = 12;
const int Resources::Inky_Down = 13;
const int Resources::Inky_Left = 14;
const int Resources::Inky_Right = 15;


const int Resources::Clyde_ghost4 = 16;
const int Resources::Clyde_Down = 17;
const int Resources::Clyde_Left = 18;
const int Resources::Clyde_Right = 19;


const int Resources::Ghost_frighten = 20;
const int Resources::Pac_dead = 21;


void Resources::loadSprite(int value, int rect1, int rect2, int animationframes)
{
	sf::IntRect* Rectan = new sf::IntRect(rect1, rect2, 15, 15);
	sf::Sprite* animate = new sf::Sprite(Texture_Objects, *Rectan);
	animate->setScale(2.0f, 2.0f);
	animate->setOrigin(7.5f, 7.5f);
	sprites.insert(std::pair<int, sf::Sprite*>(value, animate));
	animations.insert(std::pair<int, Animation>(value, Animation(Rectan, animationframes)));
}

sf::Sprite* Resources::get(int num, bool Is_animated, Direction looking)
{
	if (num != Resources::Ghost_frighten)
	{
		switch (looking)
		{
		case Direction::Down:
			num += 1;
			break;
		case Direction::Left:
			num += 2;
			break;
		case Direction::Right:
			num += 3;
			break;
		}
	}

	if (Is_animated)
	{
		animations.at(num).Frame_changer();
		sprites.at(num)->setTextureRect(animations.at(num).getBounds());
	}

	return sprites.at(num);
}

void Resources::Draw_resources()
{
	Maze_walls.loadFromFile("Resources/Maze.png");

	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Pieces_Maze[index] = new sf::Sprite(Maze_walls, sf::IntRect(i * 8, j * 8, 8, 8));
			Pieces_Maze[index]->setScale(2.0f, 2.0f);
			index++;
		}
	}

	Texture_Objects.loadFromFile("Resources/Pac_Ghost.png");

	//loading resources for pacman
	loadSprite(Resources::Pac_man, 0, 0, 3);
	loadSprite(Resources::Pac_Man_Down, 45, 0, 3);
	loadSprite(Resources::Pac_Man_Left, 90, 0, 3);
	loadSprite(Resources::Pac_Man_Right, 135, 0, 3);

	//loading resources for blinky
	loadSprite(Resources::Blinky_ghost1, 0, 15, 2);
	loadSprite(Resources::Blinky_Down, 30, 15, 2);
	loadSprite(Resources::Blinky_Left, 60, 15, 2);
	loadSprite(Resources::Blinky_Right, 90, 15, 2);

	//loading resources for pinky
	loadSprite(Resources::Pinky_ghost2, 0, 30, 2);
	loadSprite(Resources::Pinky_Down, 30, 30, 2);
	loadSprite(Resources::Pinky_Left, 60, 30, 2);
	loadSprite(Resources::Pinky_Right, 90, 30, 2);

	//loading resources for inky
	loadSprite(Resources::Inky_ghost3, 0, 45, 2);
	loadSprite(Resources::Inky_Down, 30, 45, 2);
	loadSprite(Resources::Inky_Left, 60, 45, 2);
	loadSprite(Resources::Inky_Right, 90, 45, 2);

	//loading resources for clyde
	loadSprite(Resources::Clyde_ghost4, 0, 60, 2);
	loadSprite(Resources::Clyde_Down, 30, 60, 2);
	loadSprite(Resources::Clyde_Left, 60, 60, 2);
	loadSprite(Resources::Clyde_Right, 90, 60, 2);
	loadSprite(Resources::Ghost_frighten, 120, 15, 2);
	loadSprite(Resources::Pac_dead, 0, 75, 12);


}

