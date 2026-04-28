#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameStateData.h"

namespace SnakeGame
{
	class Game;

	class GameStateRecords : public GameStateData
	{
	public:
		GameStateRecords() = default;
		~GameStateRecords() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		Game* game = nullptr;

		sf::Font font;
		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

}
