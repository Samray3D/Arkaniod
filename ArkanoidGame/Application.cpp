#include "Application.h"
#include <cstdlib>
#include <ctime>

namespace SnakeGame
{

	Application::Application(const std::string& gameName) :
		window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEGHT), "SnakeGame")
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
		game.SetWindow(&window);
	}

	Application::~Application()
	{
		game.Shutdown();
	}

	void Application::Run()
	{
		sf::Clock gameClock;

		while (window.isOpen()) {

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.HandleWindowEvents(window);

			if (!window.isOpen()) {
				break;
			}

			if (game.Update(TIME_PER_FRAME, window))
			{
				window.clear();

				game.Draw(window);

				window.display();
			}
			else
			{
				window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < TIME_PER_FRAME) {
				sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
			}
		}
	}

}