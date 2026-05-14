#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	enum class BonusType
	{
		FireBall,
		WidePlatform,
		SpeedPlatform
	};

	class Bonus
	{
	public:
		Bonus(const sf::Vector2f& position, BonusType type);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		sf::FloatRect GetGlobalBounds() const;
		bool IsActive() const { return isActive; }
		void Collect() { isActive = false; }
		BonusType GetType() const { return type; }

	private:
		sf::RectangleShape shape;
		sf::Text text;
		BonusType type;
		bool isActive = true;
		float speed = 150.f;

		void SetupVisual();
	};
}