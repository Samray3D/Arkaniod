#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	class IPlatform
	{
	public:
		virtual ~IPlatform() = default;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual sf::FloatRect GetGlobalBounds() const = 0;
		virtual sf::Vector2f GetPosition() const = 0;
		virtual void SetPosition(const sf::Vector2f& position) = 0;
		virtual float GetWidth() const = 0;
		virtual void Move(float deltaX) = 0;

	};
}