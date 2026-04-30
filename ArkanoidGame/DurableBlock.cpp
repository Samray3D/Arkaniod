#include "DurableBlock.h"

namespace SnakeGame
{
	void DurableBlock::Init(float width, float height, const std::vector<sf::Color>& colors)
	{
		Block::Init(width, height, colors[0]);

		damageColors = colors;
		hitpoints = static_cast<int>(colors.size());
		currentHitStage = 0;
		isAlive = true;
	}
	void DurableBlock::Draw(sf::RenderWindow& window)
	{
		if (isAlive)
		{
			Block::Draw(window);
		}
	}
	bool DurableBlock::OnHit()
	{
		currentHitStage++;
		if (currentHitStage < hitpoints)
		{
			shape.setFillColor(damageColors[currentHitStage]);
			return false;
		}
		else
		{
			isAlive = false;
			return true;
		}
	}

}