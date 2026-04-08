#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
	class Game;

	class GameStateRecords
	{
	public:
		GameStateRecords() = default;
		~GameStateRecords() = default;

		void Init(Game* game);
		void Shutdown();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		Game* game = nullptr;

		sf::Font font;
		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};

}
