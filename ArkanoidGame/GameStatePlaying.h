#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


namespace SnakeGame
{
	class Game;

	class GameStatePlaying
	{
	public:
		GameStatePlaying() = default;
		~GameStatePlaying() = default;

		void Init(Game* game);
		void Shutdown();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta, sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);
		void Resume();

	private:

		Game* m_game = nullptr;

		sf::Font font;
		sf::SoundBuffer hitSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		sf::RectangleShape platform;
		sf::CircleShape ball;

		sf::Vector2f ballVelocity;

		float platformWidth = 100.f;
		float platformHeight = 20.f;
		float ballRadius = 10.f;

		float platformSpeed = 400.f;
		float ballSpeed = 300.f;

		int score = 0;

		bool isBallLaunched = false;
		bool isGameOver = false;
		bool isPaused = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		sf::Sound hitSound;
		sf::Sound gameOverSound;

		void UpdatePlatformMovement(sf::RenderWindow& window);
		void UpdateBallMovement(float timeDelta);
		void CheckCollisions();
		void ResetBall();
		void UpdateUI();
		void GameOver();
	};

}