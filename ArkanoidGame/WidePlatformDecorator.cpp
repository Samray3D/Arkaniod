#include "WidePlatformDecorator.h"

namespace SnakeGame
{
	WidePlatformDecorator::WidePlatformDecorator(std::unique_ptr<IPlatform> p) :
		PlatformDecorator(std::move(p)),
		originalWidth(platform ? platform->GetWidth() : 100.f)
	{

	}

	void WidePlatformDecorator::Update(float timeDelta)
	{
		if (timeRemaining > 0.f)
		{
			timeRemaining -= timeDelta;
			if (timeRemaining <= 0.f && platform)
			{

			}
		}

		if (platform)
		{
			platform->Update(timeDelta);
		}
	}

	void WidePlatformDecorator::Draw(sf::RenderWindow& window)
	{
		if (platform)
		{
			platform->Draw(window);
		}
	}

	void WidePlatformDecorator::Move(float deltaX)
	{
		if (platform)
		{
			platform->Move(deltaX);
		}
	}

	float WidePlatformDecorator::GetWidth() const
	{
		if (timeRemaining > 0.f)
		{
			return expandedWidth;
		}
		return platform ? platform->GetWidth() : originalWidth;
	}

	sf::FloatRect WidePlatformDecorator::GetGlobalBounds() const
	{
		return platform ? platform->GetGlobalBounds() : sf::FloatRect();
	}

	sf::Vector2f WidePlatformDecorator::GetPosition() const
	{
		return platform ? platform->GetPosition() : sf::Vector2f();
	}

	void WidePlatformDecorator::SetPosition(const sf::Vector2f& position)
	{
		if (platform)
		{
			platform->SetPosition(position);
		}
	}
}