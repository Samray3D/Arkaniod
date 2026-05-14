#include "NormalBallBehavior.h"

namespace SnakeGame
{
	void NormalBallBehavior::Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta)
	{
		ball.move(velocity * timeDelta);
	}

	void NormalBallBehavior::OnBlockHit()
	{

	}

	void NormalBallBehavior::OnPlatformHit()
	{

	}
}