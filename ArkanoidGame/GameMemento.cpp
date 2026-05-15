#include "GameMemento.h"

namespace SnakeGame
{
	GameMemento::GameMemento(const sf::Vector2f& ballPos, const sf::Vector2f& ballVel, const sf::Vector2f& platformPos, int scr, int blocks) :
		ballPosition(ballPos),
		ballVelocity(ballVel),
		platformPosition(platformPos),
		score(scr),
		blocksRemaining(blocks)
	{

	}

	sf::Vector2f GameMemento::GetBallPosition() const
	{
		return ballPosition;
	}

	sf::Vector2f GameMemento::GetBallVelocity() const
	{
		return ballVelocity;
	}

	sf::Vector2f GameMemento::GetPlatformPosition() const
	{
		return platformPosition;
	}

	int GameMemento::GetScore() const
	{
		return score;
	}

	int GameMemento::GetBlocksRemaining() const
	{
		return blocksRemaining;
	}
}