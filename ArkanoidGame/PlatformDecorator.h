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
		void Move(float deltaX) override;
		virtual sf::Vector2f GetSize() const override;
		virtual void SetSize(const sf::Vector2f& size) override;


	protected:
		std::unique_ptr<IPlatform> platform;
	};
}