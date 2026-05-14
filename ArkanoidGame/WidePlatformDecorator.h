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

	private:
		float originalWidth;
		float expandedWidth = 150.f;
		float timeDelta = 10.f;
	};
}