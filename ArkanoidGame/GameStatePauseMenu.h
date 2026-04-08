#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace SnakeGame
{
	class Game;

	class GameStatePauseMenu
	{
	public:
		GameStatePauseMenu() = default;
		~GameStatePauseMenu() = default;

		void Init(Game* game);
		void Shutdown();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		Game* m_game = nullptr;

		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
		MenuItem resumeItem;
		MenuItem exitItem;
	};

}
