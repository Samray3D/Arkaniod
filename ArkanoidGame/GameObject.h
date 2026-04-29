#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;

		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void Update(float timeDelta) = 0;
		virtual sf::FloatRect GetGlobalBounds() const = 0;
		virtual sf::Vector2f GetPosition() const = 0;
		virtual void SetPosition(const sf::Vector2f& position) = 0;

		virtual bool IsAlive() const { return isAlive; }
		virtual void Destroy() { isAlive = false; }
	protected:
		bool isAlive = true;
	};
}