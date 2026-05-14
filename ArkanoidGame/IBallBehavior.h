#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	class IBallBehavior
	{
	public:
		virtual ~IBallBehavior() = default;
		virtual void Update(sf::CircleShape& ball, sf::Vector2f& velocity, float deltaTime) = 0;
		virtual void OnBlockHit() = 0;
		virtual void OnPlatformHit() = 0;
		virtual bool CanDestroyBlockDirectly() const { return false; }
		virtual float GetSpeedMultiplier() const { return 1.f; }
	};
}