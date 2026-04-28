#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameStateData.h"

namespace SnakeGame
{
	class Game;

	class GameStatePauseMenu : public GameStateData
	{
	public:
		GameStatePauseMenu() = default;
		~GameStatePauseMenu() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

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
