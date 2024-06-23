#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdlib>
#include "Resources.h"
#include "AI.h"
#include "Controller.h"
#include "Directions.h"

#include <map>

using namespace std;
using namespace sf;


int main() {

	Controller gamestates;
	RenderWindow window;

	SoundBuffer buffer;

	buffer.loadFromFile("Resources/Pacman_ost.wav");
	Sound sound;
	sound.setBuffer(buffer);

	Resources::Draw_resources();
	window.create(VideoMode(450, 600), "Pac-Man");
	gamestates.addState(new AI);
	sound.play();


	while (window.isOpen())
	{
		Event instant;
		while (window.pollEvent(instant))
		{
			switch(instant.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				gamestates.keyPressed(instant.key.code);
				break;
			case Event::KeyReleased:
				gamestates.keyReleased(instant.key.code);
				break;
			}
		}
		gamestates.loop();

		window.clear(Color::Black);
		gamestates.render(&window);
		window.display();

	}

	system("pause");
	return 0;

}