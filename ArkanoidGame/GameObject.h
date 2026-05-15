#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		virtual bool IsAlive() const { return isAlive; }
		virtual void Destroy() { isAlive = false; }
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void Update(float timeDelta) = 0;
		virtual sf::FloatRect GetGlobalBounds() const = 0;
		virtual sf::Vector2f GetPosition() const = 0;
		virtual void SetPosition(const sf::Vector2f& position) = 0;

	protected:
		bool isAlive = true;
	};
}