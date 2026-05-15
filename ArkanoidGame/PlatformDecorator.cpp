#include "PlatformDecorator.h"

namespace SnakeGame
{
	PlatformDecorator::PlatformDecorator(std::unique_ptr<IPlatform> p) : platform(std::move(p))
	{

	}

	void PlatformDecorator::Update(float timeDelta)
	{
		if (platform)
		{
			platform->Update(timeDelta);
		}
	}

	void PlatformDecorator::Draw(sf::RenderWindow& window)
	{
		if (platform)
		{
			platform->Draw(window);
		}
	}

	sf::FloatRect PlatformDecorator::GetGlobalBounds() const
	{
		return platform ? platform->GetGlobalBounds() : sf::FloatRect();
	}

	sf::Vector2f PlatformDecorator::GetPosition() const
	{
		return platform ? platform->GetPosition() : sf::Vector2f();
	}

	void PlatformDecorator::SetPosition(const sf::Vector2f& position)
	{
		if (platform)
		{
			platform->SetPosition(position);
		}
	}

	float PlatformDecorator::GetWidth() const
	{
		return platform ? platform->GetWidth() : 0.f;
	}

	void PlatformDecorator::Move(float deltaX)
	{
		if (platform) platform->Move(deltaX);
	}
}