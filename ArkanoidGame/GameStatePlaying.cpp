#include "GameStatePlaying.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "FireBallBehavior.h"

namespace SnakeGame
{
	GameStatePlaying::GameStatePlaying() : bonusTimer(0.f)
	{

	}

	void GameStatePlaying::Init(Game* game)
	{	
		m_game = game;

		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		scoreDisplay.Init(font);
		assert(hitSoundBuffer.loadFromFile(SOUNDS_PATH + "Hit.wav"));
		hitSound.setBuffer(hitSoundBuffer);
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		gameOverSound.setBuffer(gameOverSoundBuffer);
		assert(victorySoundBuffer.loadFromFile(SOUNDS_PATH + "Victory.wav"));
		victorySound.setBuffer(victorySoundBuffer);

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		platform.setSize(sf::Vector2f(platformWidth, platformHeight));
		platform.setFillColor(sf::Color::Red);
		platform.setOrigin(platformWidth / 2.f, platformHeight / 2.f);
		platform.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT - 50.f);

		ball.setRadius(ballRadius);
		ball.setFillColor(sf::Color::Yellow);
		ball.setOrigin(ballRadius, ballRadius);
		

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Press SPACE to launch ball, press ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		float startX = 20.f;
		float startY = SCREEN_HEGHT - 85.f;
		float boxSize = 20.f;
		float spacing = 10.f;

		std::vector<std::pair<sf::Color, std::string>> bonuses =
		{
			{sf::Color::Red, "damage+"},
			{sf::Color::Blue, "size"},
			{sf::Color(255, 255, 0), "speed"}
		};

		for (size_t i = 0; i < bonuses.size(); i++)
		{
			BonusIndicator indicator;

			indicator.box.setSize(sf::Vector2f(boxSize, boxSize));
			indicator.box.setFillColor(bonuses[i].first);
			indicator.box.setOutlineColor(sf::Color::White);
			indicator.box.setOutlineThickness(1.f);
			indicator.box.setPosition(startX + i * (boxSize + spacing * 3), startY);

			
		}

		scoreSubject.AddObserver(&scoreDisplay);
		ballContext.SetBehavior(std::make_unique<NormalBallBehavior>());
		auto basePlatform = std::make_unique<Platform>();
		basePlatform->Init(platformWidth, platformHeight, sf::Color::Red);
		currentPlatform = std::move(basePlatform);

		isGameOver = false;
		isVictory = false;
		isBallLaunched = false;
		isPaused = false;
		SpawnBlocks();
		ResetBall();
		UpdateUI();


	}

	void GameStatePlaying::Shutdown()
	{
		
	}

	void GameStatePlaying::HandleWindowEvent(const sf::Event& event)
	{
		if (isGameOver) return;

		if (isVictory)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Y)
				{
					Init(m_game);
				}
				else if (event.key.code == sf::Keyboard::N)
				{
					m_game->SwitchStateTo(GameStateType::MainMenu);
				}
			}
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				isPaused = true;
				m_game->PushState(GameStateType::ExitDialog, true);
			}
			else if (event.key.code == sf::Keyboard::Space && !isBallLaunched)
			{
				isBallLaunched = true;
			}
			else if (event.key.code == sf::Keyboard::F5)
			{
				SaveGame();
			}
			else if (event.key.code == sf::Keyboard::F6)
			{
				LoadGame();
			}
		}
	}

	void GameStatePlaying::Update(float timeDelta)
	{

	}

	void GameStatePlaying::Update(float timeDelta, sf::RenderWindow& window)
	{
		if (isGameOver || isVictory || isPaused) return;

		if (bonusTimer > 0.f)
		{
			bonusTimer -= timeDelta;
			if (bonusTimer <= 0.f)
			{
				ballContext.SetBehavior(std::make_unique<NormalBallBehavior>());
				ballSpeed = 300.f;

				float length = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
				if (length > 0)
				{
					ballVelocity.x = ballVelocity.x / length * ballSpeed;
					ballVelocity.y = ballVelocity.y / length * ballSpeed;
				}
			}
		}

		for (auto& bonus : bonuses)
		{
			bonus.Update(timeDelta);
		}

		UpdatePlatformMovement(window);
		CheckBonusCollisions();
		
		if (isBallLaunched)
		{
			UpdateBallMovement(timeDelta);
			CheckCollisions();
			CheckBlockCollisions();
		}
	}

	void GameStatePlaying::Resume()
	{
		isPaused = false;
	}

	void GameStatePlaying::Draw(sf::RenderWindow& window)
	{
		window.draw(background);

		for (auto& block : blocks)
		{
			block.Draw(window);
		}

		for (auto& durableBlock : durableBlocks)
		{
			durableBlock.Draw(window);
		}

		for (auto& bonus : bonuses)
		{
			bonus.Draw(window);
		}

		if (currentPlatform)
		{
			currentPlatform->Draw(window);
		}
		else
		{
			window.draw(platform);
		}
		window.draw(ball);
		scoreDisplay.Draw(window);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);

		if (isVictory)
		{
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setCharacterSize(48);
			gameOverText.setFillColor(sf::Color::Yellow);
			gameOverText.setString("VICTORY");
			gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 0.5f }));
			gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f - 50.f);
			window.draw(gameOverText);

			sf::Text restartText;
			restartText.setFont(font);
			restartText.setCharacterSize(24);
			restartText.setFillColor(sf::Color::White);
			restartText.setString("Play again? (Y/N) ?");
			restartText.setOrigin(GetTextOrigin(restartText, { 0.5f, 0.5f }));
			restartText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f + 20.f);
			window.draw(restartText);
		}
		
		if (isGameOver)
		{
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setCharacterSize(48);
			gameOverText.setFillColor(sf::Color::Green);
			gameOverText.setString("GAME OVER");
			gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 0.5f }));
			gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f + 20.f);
			window.draw(gameOverText);
		}
	}

	void GameStatePlaying::UpdatePlatformMovement(sf::RenderWindow& window)
	{
		sf::Vector2f platformPos = platform.getPosition();
		bool isMovingByKeyboard = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			platformPos.x -= platformSpeed * 1.f / 60.f;
			isMovingByKeyboard = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			platformPos.x += platformSpeed * 1.f / 60.f;
			isMovingByKeyboard = true;
		}
		if (!isMovingByKeyboard)
		{
			sf::Vector2i mousePosPixels = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosPixels);

			if (mousePosWorld.x >= 0 && mousePosWorld.x <= SCREEN_WIDTH)
			{
				platformPos.x = mousePosWorld.x;
			}
		}
		platformPos.x = std::max(platformWidth / 2.f, std::min(platformPos.x, SCREEN_WIDTH - platformWidth / 2.f));
		platformPos.y = SCREEN_HEGHT - 50.f;
		platform.setPosition(platformPos);

		if (currentPlatform)
		{
			currentPlatform->SetPosition(platformPos);
		}
		
	}

	void GameStatePlaying::UpdateBallMovement(float timeDelta)
	{
		ball.move(ballVelocity * timeDelta);
		if (ball.getPosition().x - ballRadius <= 0.f)
		{
			ballVelocity.x = std::abs(ballVelocity.x);
			hitSound.play();
		}
		else if (ball.getPosition().x + ballRadius >= SCREEN_WIDTH)
		{
			ballVelocity.x = -std::abs(ballVelocity.x);
			hitSound.play();
		}
		else if (ball.getPosition().y - ballRadius <= 0.f)
		{
			ballVelocity.y = std::abs(ballVelocity.y);
			hitSound.play();
		}
		else if (ball.getPosition().y + ballRadius >= SCREEN_HEGHT)
		{
			SaveGame();
			GameOver();
		}
	}

	void GameStatePlaying::CheckCollisions()
	{
		sf::FloatRect ballBounds = ball.getGlobalBounds();
		sf::FloatRect platformBounds = platform.getGlobalBounds();

		if (ballBounds.intersects(platformBounds))
		{
			float hitPoint = ball.getPosition().x - platform.getPosition().x;
			float normalizedHitPoint = hitPoint / (platformWidth / 2.f);

			ballVelocity.x = normalizedHitPoint * ballSpeed;
			ballVelocity.y = -std::abs(ballVelocity.y);

			float length = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
			if (length > 0)
			{
				ballVelocity.x = ballVelocity.x / length * ballSpeed;
				ballVelocity.y = ballVelocity.y / length * ballSpeed;
			}
			hitSound.play();
			UpdateUI();
		}
	}

	void GameStatePlaying::ResetBall()
	{
		ball.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT - 100.f);
		ballVelocity = sf::Vector2f(ballSpeed, -ballSpeed);
	}

	void GameStatePlaying::UpdateUI()
	{
		
	}


	void GameStatePlaying::SpawnBlocks()
	{
		blocks.clear();
		durableBlocks.clear();
		blocksRemaining = 0;
		
		float blockWidth = 70.f;
		float blockHeight = 25.f;
		float startX = 100.f;
		float startY = 100.f;
		float spacingX = 10.f;
		float spacingY = 10.f;

		std::vector<sf::Color> colors =
		{
			sf::Color::Green, sf::Color::Yellow, sf::Color::Yellow,
			sf::Color::Yellow, sf::Color::Yellow, sf::Color::Yellow, sf::Color::Yellow
		};

		std::vector<sf::Color> durableColors =
		{
			sf::Color::Green, sf::Color::Magenta, sf::Color::Red, sf::Color::Yellow
		};
		
		for (int row = 0; row < 5; ++row)
		{
			for (int col = 0; col < 8; ++col)
			{
				float x = startX + col * (blockWidth + spacingX);
				float y = startY + row * (blockHeight + spacingY);
				if (row == 4)
				{
					DurableBlock durableBlock;
					durableBlock.Init(blockWidth, blockHeight, durableColors);
					durableBlock.SetPosition(sf::Vector2f(x, y));
					durableBlocks.push_back(durableBlock);
					blocksRemaining++;
				}
				else
				{
					Block block;
					block.Init(blockWidth, blockHeight, sf::Color::Yellow);
					block.SetPosition(sf::Vector2f(x, y));
					blocks.push_back(block);
					blocksRemaining++;
				}
			}
		}
	}

	void GameStatePlaying::CheckBlockCollisions()
	{
		sf::FloatRect ballBounds = ball.getGlobalBounds();
		bool ballCanPasThrough = ballContext.CanDestroyBlockDirectly();
		float speedMultiplier = ballContext.GetSpeedMultiplier();
		ballSpeed = 300.f * speedMultiplier;

		for (auto& block : blocks)
		{
			if (block.IsAlive() && ballBounds.intersects(block.GetGlobalBounds()))
			{
				if (!ballCanPasThrough)
				{
					sf::FloatRect blockBounds = block.GetGlobalBounds();
					float overlapLeft = ballBounds.left + ballBounds.width - blockBounds.left;
					float overlapRight = blockBounds.left + blockBounds.width - ballBounds.left;
					float overlapTop = ballBounds.top + ballBounds.height - blockBounds.top;
					float overlapBottom = blockBounds.top + blockBounds.height - ballBounds.top;

					if (std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom))
					{
						ballVelocity.x = -ballVelocity.x;
					}
					else
					{
						ballVelocity.y = -ballVelocity.y;
					}
				}
				block.Destroy();
				blocksRemaining--;

				scoreSubject.NotifyBlockDestroyed(10);
				if (rand() % 100 < 10)
				{
					SpawnBonus(block.GetPosition());
				}

				ballContext.OnBlockHit();
				hitSound.play();
				UpdateUI();

				if (blocksRemaining == 0 && durableBlocks.empty())
				{
					Victory();
					return;
				}
			
			}
		}
		for (auto& durableBlock : durableBlocks)
		{
			if (durableBlock.IsAlive() && ballBounds.intersects(durableBlock.GetGlobalBounds()))
			{
				sf::FloatRect blockBounds = durableBlock.GetGlobalBounds();
				float overlapLeft = ballBounds.left + ballBounds.width - blockBounds.left;
				float overlapRight = blockBounds.left + blockBounds.width - ballBounds.left;
				float overlapTop = ballBounds.top + ballBounds.height - blockBounds.top;
				float overlapBottom = blockBounds.top + blockBounds.height - ballBounds.top;

				if (!ballCanPasThrough)
				{
					
					if (std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom))
					{
						ballVelocity.x = -ballVelocity.x;
						if (overlapLeft < overlapRight)
						{
							ball.setPosition(blockBounds.left - ballRadius - 1.f, ball.getPosition().y);
						}
						else
						{
							ball.setPosition(blockBounds.left + blockBounds.width + ballRadius + 1.f, ball.getPosition().y);
						}
					}
					else
					{
						ballVelocity.y = -ballVelocity.y;
						if (overlapTop < overlapBottom)
						{
							ball.setPosition(ball.getPosition().x, blockBounds.top - ballRadius - 1.f);
						}
						else
						{
							ball.setPosition(ball.getPosition().x, blockBounds.top + blockBounds.height + ballRadius + 1.f);
						}
					}
				}

				ballBounds = ball.getGlobalBounds();

				bool isDestroyed = durableBlock.OnHit();

				if (isDestroyed)
				{
					blocksRemaining--;
					scoreSubject.NotifyBlockDestroyed(30);
					if (rand() % 100 < 10)
					{
						SpawnBonus(durableBlock.GetPosition());
					}
				}

				else

				{
					scoreSubject.NotifyBlockDestroyed(5);
				}

				ballContext.OnBlockHit();
				hitSound.play();
				UpdateUI();
				if (blocksRemaining == 0)
				{
					Victory();
					return;
				}
				
			}

		}
	}

	void GameStatePlaying::SpawnBonus(const sf::Vector2f& position)
	{
		int bonusType = rand() % 3;
		BonusType type;

		switch (bonusType)
		{
		case 0: type = BonusType::FireBall; break;
		case 1: type = BonusType::WidePlatform; break;
		default: type = BonusType::SpeedBall; break;
		}
		bonuses.emplace_back(position, type);
	}

	void GameStatePlaying::CheckBonusCollisions()
	{
		if (!currentPlatform) return;

		sf::FloatRect platformBounds = currentPlatform->GetGlobalBounds();

		for (auto it = bonuses.begin(); it != bonuses.end();)
		{
			if (!it->IsActive())
			{
				it = bonuses.erase(it);
				continue;
			}

			if (it->GetGlobalBounds().intersects(platformBounds))
			{
				ApplyBonus(it->GetType());
				it = bonuses.erase(it);
			}
			else if (it->GetGlobalBounds().top + it->GetGlobalBounds().height > SCREEN_HEGHT)
			{
				it = bonuses.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void GameStatePlaying::ApplyBonus(BonusType type)
	{
		sf::Vector2f currentPos = platform.getPosition();

		switch (type)
		{
		case BonusType::FireBall:
			ballContext.SetBehavior(std::make_unique<FireBallBehavior>());
			bonusTimer = 10.f;
			break;
		case BonusType::WidePlatform:
			currentPlatform = std::make_unique<WidePlatformDecorator>(std::move(currentPlatform));
			static_cast<WidePlatformDecorator*>(currentPlatform.get())->ApplyEffect();
			break;
		case BonusType::SpeedBall:
			ballSpeed = 600.f;
			float length = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
			if (length > 0)
			{
				ballVelocity.x = ballVelocity.x / length * ballSpeed;
				ballVelocity.y = ballVelocity.y / length * ballSpeed;
			}
			bonusTimer = 5.f;
			break;

		}
		if (currentPlatform)
		{
			currentPlatform->SetPosition(currentPos);
		}
	}

	void GameStatePlaying::GameOver()
	{
		if (isGameOver) return;

		isGameOver = true;
		isBallLaunched = false;
		gameOverSound.play();

		m_game->SetLastScore(scoreDisplay.GetCurrentScore());
		m_game->UpdateRecord(PLAYER_NAME, scoreDisplay.GetCurrentScore());
		m_game->SwitchStateTo(GameStateType::GameOver);
		
	}

	void GameStatePlaying::Victory()
	{
		if (isVictory) return;

		isVictory = true;
		isBallLaunched = false;
		ballVelocity = sf::Vector2f(0.f, 0.f);
		victorySound.play();
	}

	void GameStatePlaying::SaveGame()
	{
		std::vector<bool> blocksState;
		for (const auto& block : blocks)
		{
			blocksState.push_back(block.IsAlive());
		}
		for (const auto& block : durableBlocks)
		{
			blocksState.push_back(block.IsAlive());
		}

		auto memento = std::make_unique<GameMemento>(
			ball.getPosition(),
			ballVelocity,
			platform.getPosition(),
			scoreDisplay.GetCurrentScore(),
			blocksRemaining
		);

		memento->SetBlocks(blocksState);
		saveManager.SaveState(std::move(memento));
		printf("Game saved!\n");
	}

	void GameStatePlaying::LoadGame()
	{
		if (!saveManager.HasSavedState())
		{
			printf("No saved game found!\n");
			return;
		}

		auto memento = saveManager.LoadLastState();
		if (memento)
		{
			ball.setPosition(memento->GetBallPosition());
			ballVelocity = memento->GetBallVelocity();

			platform.setPosition(memento->GetPlatformPosition());
			if (currentPlatform)
			{
				currentPlatform->SetPosition(memento->GetPlatformPosition());
			}

			scoreDisplay.OnScoreChanged(memento->GetScore());
		}
	}
}
