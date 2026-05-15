#pragma once
#include "IPlatform.h"

namespace SnakeGame
{
	class Platform : public IPlatform
	{
	public:
		Platform();
		void Init(float width, float height, const sf::Color& color);
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		sf::FloatRect GetGlobalBounds() const override;
		sf::Vector2f GetPosition() const override;
		void SetPosition(const sf::Vector2f& position) override;
		float GetWidth() const override { return width; }
		void Move(float deltaX) override;

	private:
		sf::RectangleShape shape;
		float width = 100.f;
		float height = 20.f;
		float speed = 400.f;
	};
}