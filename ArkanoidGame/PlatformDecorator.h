#pragma once
#include "IPlatform.h"
#include <memory>

namespace SnakeGame
{
	class PlatformDecorator : public IPlatform
	{
	public:
		PlatformDecorator(std::unique_ptr<IPlatform> platform);
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		sf::FloatRect GetGlobalBounds() const override;
		sf::Vector2f GetPosition() const override;
		void SetPosition(const sf::Vector2f& position) override;
		float GetWidth() const override;
	protected:
		std::unique_ptr<IPlatform> platform;
	};
}