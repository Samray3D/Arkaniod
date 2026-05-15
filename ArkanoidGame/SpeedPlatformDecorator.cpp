#include "SpeedPlatformDecorator.h"

namespace SnakeGame
{
	SpeedPlatformDecorator::SpeedPlatformDecorator(std::unique_ptr<IPlatform> p) :
		PlatformDecorator(std::move(p)),
		originalSpeed(400.f)
	{
		if (platform)
		{

		}
	}

	void SpeedPlatformDecorator::Update(float timeDelta)
	{
		if (timeRemaining > 0.f)
		{
			timeRemaining -= timeDelta;
		}

		if (platform)
		{
			platform->Update(timeDelta);
		}
	}

	void SpeedPlatformDecorator::Draw(sf::RenderWindow& window)
	{
		if (platform)
		{
			platform->Draw(window);
		}
	}

	float SpeedPlatformDecorator::GetWidth() const
	{
		return platform ? platform->GetWidth() : 100.f;
	}

	void SpeedPlatformDecorator::Move(float deltaX)
	{
		if (!platform) return;
		float effectiveDelta = deltaX;
		if (timeRemaining > 0.f)
		{
			float speedMultiplier = boostedSpeed / originalSpeed;
			effectiveDelta = deltaX * speedMultiplier;
		}
		platform->Move(effectiveDelta);
	}

	sf::FloatRect SpeedPlatformDecorator::GetGlobalBounds() const
	{
		return platform ? platform->GetGlobalBounds() : sf::FloatRect();
	}

	sf::Vector2f SpeedPlatformDecorator::GetPosition() const
	{
		return platform ? platform->GetPosition() : sf::Vector2f();
	}

	void SpeedPlatformDecorator::SetPosition(const sf::Vector2f& position)
	{
		if (platform)
		{
			platform->SetPosition(position);
		}
	}
}