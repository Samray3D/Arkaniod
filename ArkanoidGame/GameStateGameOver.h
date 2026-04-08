#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	class Game;

	class GameStateGameOver
	{
	public:
		GameStateGameOver() = default;
		~GameStateGameOver() = default;

		void Init(Game* game);
		void Shutdown();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
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
