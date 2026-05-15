#include "Bonus.h"
#include "Text.h"

namespace SnakeGame
{
	Bonus::Bonus(const sf::Vector2f& position, BonusType bonusType) : type(bonusType)
	{
		shape.setSize(sf::Vector2f(30.f, 30.f));
		shape.setOrigin(15.f, 15.f);
		shape.setPosition(position);
		SetupVisual();
	}
	
	void Bonus::SetupVisual()
	{
		switch (type)
		{
		case BonusType::FireBall:
			shape.setFillColor(sf::Color::Red);
			break;
		case BonusType::WidePlatform:
			shape.setFillColor(sf::Color::Blue);
			break;
		case BonusType::SpeedPlatform:
			shape.setFillColor(sf::Color::Green);
			break;
		}
	}

	void Bonus::Update(float timeDelta)
	{
		if (isActive)
		{
			shape.move(0.f, speed * timeDelta);
		}
	}

	void Bonus::Draw(sf::RenderWindow& window)
	{
		if (isActive)
		{
			window.draw(shape);
		}
	}

	sf::FloatRect Bonus::GetGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}

	bool Bonus::IsActive() const
	{
		return isActive;
	}

	void Bonus::Collect()
	{
		isActive = false;
	}

	BonusType Bonus::GetType() const
	{
		return type;
	}
}