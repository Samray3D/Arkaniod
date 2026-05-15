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

	void GameMemento::SetBlocks(const std::vector<bool>& blocksState)
	{
		this->blockState = blocksState;
	}

	std::vector<bool> GameMemento::GetBlocksState() const
	{
		return blockState;
	}
}