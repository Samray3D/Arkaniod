#pragma once
#include "PlatformDecorator.h"

namespace SnakeGame
{
	class WidePlatformDecorator : public PlatformDecorator
	{
	public:
		WidePlatformDecorator(std::unique_ptr<IPlatform> platform);
		void Draw(sf::RenderWindow& window) override;
		float GetWidth() const override;
		void Update(float timeDelta) override;
		void Move(float deltaX) override;
		sf::FloatRect GetGlobalBounds() const override;
		sf::Vector2f GetPosition() const override;
		void SetPosition(const sf::Vector2f& position) override;
		void ApplyEffect();


	private:
		float originalWidth;
		float expandedWidth = 150.f;
		float timeRemaining = 10.f;
	};
}