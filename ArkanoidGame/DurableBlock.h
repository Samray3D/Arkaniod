#pragma once
#include "Block.h"
#include <vector>

namespace SnakeGame
{
	class DurableBlock : public Block
	{
	public:
		DurableBlock() = default;
		~DurableBlock() = default;

		void Init(float width, float height, const std::vector<sf::Color>& damageColors);
		void Draw(sf::RenderWindow& window) override;
		bool OnHit();

	private:
		int hitpoints = 3;
		std::vector<sf::Color> damageColors;
		int currentHitStage = 0;

	};
}