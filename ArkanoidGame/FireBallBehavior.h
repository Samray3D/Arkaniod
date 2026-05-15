#pragma once
#include "IBallBehavior.h"

namespace SnakeGame
{
	class FireBallBehavior : public IBallBehavior
	{
	public:
		void Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta) override;
		void OnBlockHit() override;
		void OnPlatformHit() override;
		bool CanDestroyBlockDirectly() const override { return true; }
		float GetSpeedMultiplier() const override { return 1.5f; }

	private:
		int blocksHitInRow = 0;
	};
}