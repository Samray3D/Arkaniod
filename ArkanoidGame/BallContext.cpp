#include "BallContext.h"

namespace SnakeGame
{
	void BallContext::SetBehavior(std::unique_ptr<IBallBehavior> newBehavior)
	{
		behavior = std::move(newBehavior);
	}

	void BallContext::Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta)
	{
		if (behavior)
		{
			behavior->Update(ball, velocity, timeDelta);
		}
	}

	void BallContext::OnBlockHit()
	{
		if (behavior)
		{
			behavior->OnBlockHit();
		}
	}

	void BallContext::OnPlatformHit()
	{
		if (behavior)
		{
			behavior->OnPlatformHit();
		}
	}

	bool BallContext::CanDestroyBlockDirectly() const
	{
		return behavior ? behavior->CanDestroyBlockDirectly() : false;
	}

	float BallContext::GetSpeedMultiplier() const
	{
		return behavior ? behavior->GetSpeedMultiplier() : 1.f;
	}
}