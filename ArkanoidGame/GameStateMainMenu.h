#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace SnakeGame
{
	class Game;

	class GameStateMainMenu
	{
	public:
		GameStateMainMenu() = default;
		~GameStateMainMenu() = default;

		void Init(Game* game);
		void Shutdown();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		Game* m_game = nullptr;

		sf::Font font;

		MenuItem startGameItem;
		MenuItem optionsItem;
		MenuItem recordsItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

}
