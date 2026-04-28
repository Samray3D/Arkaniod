#include "Block.h"

namespace SnakeGame
{
	Block::Block()
	{
		Init(50.f, 20.f, sf::Color::Blue);
	}
	Block::Block(const sf::Color& color)
	{
		Init(50.f, 20.f, color);
	}
	void Block::Init(float width, float height, const sf::Color& color)
	{
		shape.setSize(sf::Vector2f(width, height));
		shape.setFillColor(color);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1.f);
		shape.setOrigin(width / 2.f, height / 2.f);
		isAlive = true;
	}
	void Block::Draw(sf::RenderWindow& window)
	{
		if (isAlive)
		{
			window.draw(shape);
		}
	}
	void Block::Update(float timeDelta)
	{

	}
	sf::FloatRect Block::GetGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}
	sf::Vector2f Block::GetPosition() const
	{
		return shape.getPosition();
	}
	
	void Block::SetPosition(const sf::Vector2f& position)
	{
		shape.setPosition(position);
	}
}