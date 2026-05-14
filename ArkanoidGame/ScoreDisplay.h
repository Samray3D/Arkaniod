#pragma once
#include "IScoreObserver.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	class ScoreDisplay : public IScoreObserver
	{
	public:
		ScoreDisplay(sf::Font& font);
		void OnScoreChanged(int newScore) override;
		void OnBlockDestroyed(int points) override;
		void Draw(sf::RenderWindow& window);
		int GetCurrentScore() const { return currentScore; }

	private:
		sf::Text scoreText;
		int currentScore = 0;
	};
}
