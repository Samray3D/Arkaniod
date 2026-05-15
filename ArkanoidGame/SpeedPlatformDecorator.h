#pragma once
#include "PlatformDecorator.h"

namespace SnakeGame
{
	class SpeedPlatformDecorator : public PlatformDecorator
	{
	public:
		SpeedPlatformDecorator(std::unique_ptr<IPlatform> platform);
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		float GetWidth() const override;
		void Move(float deltaX) override;
		sf::FloatRect GetGlobalBounds() const override;
		sf::Vector2f GetPosition() const override;
		void SetPosition(const sf::Vector2f& position) override;


	private:
		float originalSpeed;
		float boostedSpeed = 600.f;
		float timeRemaining = 8.f;
	};
}