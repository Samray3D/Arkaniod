#include "FireBallBehavior.h"

namespace SnakeGame
{
	void FireBallBehavior::Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta)
	{
		ball.move(velocity * timeDelta);
	}

	void FireBallBehavior::OnBlockHit()
	{
		blocksHitInRow++;
	}

	void FireBallBehavior::OnPlatformHit()
	{
		blocksHitInRow = 0;
	}
}