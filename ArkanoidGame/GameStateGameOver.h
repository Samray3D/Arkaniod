#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateData.h"

namespace SnakeGame
{
	class Game;

	class GameStateGameOver : public GameStateData
	{
	public:
		GameStateGameOver() = default;
		~GameStateGameOver() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void SetScore(int score) { m_score = score; } 

	private:
		Game* m_game = nullptr;
		sf::Font font;
		float timeSinceGameOver = 0.f;
		int m_score = 0;
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
	};

}
