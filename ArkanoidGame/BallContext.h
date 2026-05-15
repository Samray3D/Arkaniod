#pragma once
#include <memory>
#include "IBallBehavior.h"
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	class BallContext
	{
	public:
		void SetBehavior(std::unique_ptr<IBallBehavior> behavior);
		void Update(sf::CircleShape& ball, sf::Vector2f& velocity, float timeDelta);
		void OnBlockHit();
		void OnPlatformHit();
		bool CanDestroyBlockDirectly() const;
		float GetSpeedMultiplier() const;
	private:
		std::unique_ptr<IBallBehavior> behavior;
	};
}