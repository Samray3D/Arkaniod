#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace SnakeGame
{
	class Block : public GameObject
	{
	public:
		Block();
		explicit Block(const sf::Color& color);

		void Init(float width, float height, const sf::Color& color);
		void Draw(sf::RenderWindow& window) override;
		void Update(float timeDelta) override;
		sf::FloatRect GetGlobalBounds() const override;
		sf::Vector2f GetPosition() const override;
		void SetPosition(const sf::Vector2f& position) override;
		bool IsAlive() const { return isAlive; }
		void Destroy() { isAlive = false; }

	protected:
		sf::RectangleShape shape;
	};
}