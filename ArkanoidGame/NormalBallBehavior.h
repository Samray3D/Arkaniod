#pragma once
#include "IBallBehavior.h"

namespace SnakeGame
{
	class NormalBallBehavior : public IBallBehavior
	{
	public:
		void Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta) override;
		void OnBlockHit() override;
		void OnPlatformHit() override;
	};
}