#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include <vector>
#include "Block.h"



namespace SnakeGame
{
	class Game;

	class GameStatePlaying : public GameStateData
	{
	public:
		GameStatePlaying() = default;
		~GameStatePlaying() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Update(float timeDelta, sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window) override;
		void Resume() override;

	private:

		Game* m_game = nullptr;

		sf::Font font;
		sf::SoundBuffer hitSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer victorySoundBuffer;

		sf::RectangleShape platform;
		sf::CircleShape ball;

		sf::Vector2f ballVelocity;

		float platformWidth = 100.f;
		float platformHeight = 20.f;
		float ballRadius = 10.f;

		float platformSpeed = 400.f;
		float ballSpeed = 300.f;

		int score = 0;
		int blocksRemaining = 0;

		bool isBallLaunched = false;
		bool isGameOver = false;
		bool isVictory = false;
		bool isPaused = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		std::vector<Block> blocks;

		sf::Sound hitSound;
		sf::Sound gameOverSound;
		sf::Sound victorySound;

		void UpdatePlatformMovement(sf::RenderWindow& window);
		void UpdateBallMovement(float timeDelta);
		void CheckCollisions();
		void CheckBlockCollisions();
		void ResetBall();
		void UpdateUI();
		void GameOver();
		void Victory();
		void SpawnBlocks();
	};

}