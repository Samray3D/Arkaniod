#include "Platform.h"
#include "GameSettings.h"

namespace SnakeGame
{
	Platform::Platform() :
		width(100.f),
		height(20.f),
		speed(400.f)
	{

	}

	void Platform::Init(float w, float h, const sf::Color& color)
	{
		width = w;
		height = h;
		shape.setSize(sf::Vector2f(width, height));
		shape.setFillColor(color);
		shape.setOrigin(width / 2.f, height / 2.f);
	}

	void Platform::Update(float timeDelta)
	{

	}

	void Platform::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::FloatRect Platform::GetGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}

	sf::Vector2f Platform::GetPosition() const
	{
		return shape.getPosition();
	}

	void Platform::SetPosition(const sf::Vector2f& position)
	{
		shape.setPosition(position);
	}

	void Platform::Move(float deltaX)
	{
		shape.move(deltaX, 0.f);
	}
}