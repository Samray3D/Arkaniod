#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	class Block
	{
	public:
		Block();
		explicit Block(const sf::Color& color);

		void Init(float width, float height, const sf::Color& color);
		void Draw(sf::RenderWindow& window);
		void Update(float timeDelta);
		sf::FloatRect GetGlobalBounds() const;
		sf::Vector2f GetPosition() const;
		void SetPosition(const sf::Vector2f& position);

		bool IsAlive() const { return isAlive; }
		void Destroy() { isAlive = false; }
	private:
		sf::RectangleShape shape;
		bool isAlive = true;
	};
}