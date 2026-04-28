#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace SnakeGame
{
	class Game;

	class GameStateMainMenu : public GameStateData
	{
	public:
		GameStateMainMenu() = default;
		~GameStateMainMenu() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

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
