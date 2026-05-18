#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include <vector>
#include "Block.h"
#include "DurableBlock.h"
#include "ScoreSubject.h"
#include "ScoreDisplay.h"
#include "BallContext.h"
#include "IPlatform.h"
#include "Platform.h"
#include "SaveManager.h"
#include "Bonus.h"
#include "NormalBallBehavior.h"
#include "FireBallBehavior.h"
#include "WidePlatformDecorator.h"
#include "SpeedPlatformDecorator.h"
#include "GameStateData.h"



namespace SnakeGame
{
	
	class Game;

	class GameStatePlaying : public GameStateData
	{
	public:
		GameStatePlaying();
		~GameStatePlaying() = default;

		void Init(Game* game) override;
		void Shutdown() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Update(float timeDelta, sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window) override;
		void Resume() override;

		void SaveGame();
		void LoadGame();

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

		

		bool isBallLaunched = false;
		bool isGameOver = false;
		bool isVictory = false;
		bool isPaused = false;

	
		sf::Text inputHintText;
		sf::RectangleShape background;

		std::vector<Block> blocks;
		std::vector<DurableBlock> durableBlocks;
		int blocksRemaining = 0;

		sf::Sound hitSound;
		sf::Sound gameOverSound;
		sf::Sound victorySound;

		ScoreSubject scoreSubject;
		ScoreDisplay scoreDisplay;
		
		BallContext ballContext;

		std::unique_ptr<IPlatform> currentPlatform;

		SaveManager saveManager;

		std::vector<Bonus> bonuses;
		float bonusTimer = 0.f;

		struct BonusIndicator
		{
			sf::RectangleShape box;
			sf::Text description;
		};
		std::vector<BonusIndicator> bonusIndicator;

		int lives = 3;

		
		void UpdatePlatformMovement(sf::RenderWindow& window);
		void UpdateBallMovement(float timeDelta);
		void CheckCollisions();
		void CheckBlockCollisions();
		void ResetBall();
		void UpdateUI();
		void GameOver();
		void Victory();
		void SpawnBlocks();
		void SpawnBonus(const sf::Vector2f& position);
		void CheckBonusCollisions();
		void ApplyBonus(BonusType type);
	};

}