#include "ScoreDisplay.h"
#include "Text.h"

namespace SnakeGame
{
	void ScoreDisplay::Init(sf::Font& font)
	{
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(10.f, 10.f);
	}

	void ScoreDisplay::OnScoreChanged(int newScore)
	{
		currentScore = newScore;
		scoreText.setString("Score: " + std::to_string(currentScore));
	}

	void ScoreDisplay::OnBlockDestroyed(int points)
	{
		currentScore += points;
		scoreText.setString("Score: " + std::to_string(currentScore));
	}

	void ScoreDisplay::Draw(sf::RenderWindow& window)
	{
		window.draw(scoreText);
	}
}