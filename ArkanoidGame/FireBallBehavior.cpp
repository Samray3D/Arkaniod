#include "FireBallBehavior.h"

namespace SnakeGame
{
	void FirelBallBehavior::Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta)
	{
		ball.move(velocity * timeDelta);
	}

	void FirelBallBehavior::OnBlockHit()
	{
		blocksHitInRow++;
	}

	void FirelBallBehavior::OnPlatformHit()
	{
		blocksHitInRow = 0;
	}
}