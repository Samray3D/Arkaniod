#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame
{

	class Game;

	class GameStateData
	{
	public:
		virtual ~GameStateData() = default;

		virtual void Init(Game* game) = 0;
		virtual void HandleWindowEvent(const sf::Event& event) = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void Resume() {}
	};
}