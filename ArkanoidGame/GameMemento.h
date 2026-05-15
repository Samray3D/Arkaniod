#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	class GameMemento
	{
	public:
		GameMemento(const sf::Vector2f& ballPos, const sf::Vector2f& ballVel, const sf::Vector2f& platformPos, int score, int blocksRemaining);
		sf::Vector2f GetBallPosition() const;
		sf::Vector2f GetBallVelocity() const;
		sf::Vector2f GetPlatformPosition() const;
		int GetScore() const;
		int GetBlocksRemaining() const;
		void SetBlocks(const std::vector<bool>& blocksState);
		std::vector<bool> GetBlocksState() const;

	private:
		sf::Vector2f ballPosition;
		sf::Vector2f ballVelocity;
		sf::Vector2f platformPosition;
		int score;
		int blocksRemaining;
		std::vector<bool> blockState;
	};
}