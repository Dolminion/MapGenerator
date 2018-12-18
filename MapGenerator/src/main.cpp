#include <SFML/Graphics.hpp>
#include "generator.h"

unsigned int windowSize();

int main()
{
	int iMapSize = 150;
	unsigned int uiWindowSize = windowSize();
	sf::RenderWindow window(sf::VideoMode(unsigned int(uiWindowSize * 1.5), uiWindowSize), "Map Generator", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(int(uiWindowSize * 0.15), int(uiWindowSize * 0.025)));
	window.setKeyRepeatEnabled(false);

	//random number seed
	srand(time(NULL));

	//Create Clock to create real-time effects
	sf::Clock timer;
	float fFps = 60.f;
	float fFrameTime = 1.f / fFps;
	float fElapsedTime;

	Generator generator
	(
		uiWindowSize,
		fFps,
		iMapSize
	);

	if (!generator.loadFont(".\\assets\\fonts\\ASCOTA Regular.otf"))
	{
		return 0;
	}

	sf::Event event;

	while (window.isOpen())
	{

		//event handling
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					generator.processClick(window);
				}
				/*if (event.mouseButton.button == sf::Mouse::Middle)
				{
					generator.smoothMap();
				}*/
			}
		}

		if (generator.exit())
			window.close();

		fElapsedTime = timer.getElapsedTime().asSeconds();

		if (fElapsedTime > fFrameTime)
		{
			generator.update(fElapsedTime, window);

			timer.restart();

			//clear the window
			window.clear();

			//draw the new window
			window.draw(generator);

			//display the window
			window.display();
		}
	}

	return 0;
}

unsigned int windowSize()
{
	unsigned int height = sf::VideoMode::getDesktopMode().height;
	float size;
	float multiplier = 0.9f;

	size = float(height * multiplier);

	return size;
}