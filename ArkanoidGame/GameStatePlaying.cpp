#include "GameStatePlaying.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void GameStatePlaying::Init(Game* game)
	{	
		m_game = game;

		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(hitSoundBuffer.loadFromFile(SOUNDS_PATH + "Hit.wav"));
		hitSound.setBuffer(hitSoundBuffer);
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		gameOverSound.setBuffer(gameOverSoundBuffer);

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
		
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(10.f, 10.f);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Press SPACE to launch ball, press ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		score = 0;
		isGameOver = false;
		isBallLaunched = false;
		ResetBall();
		UpdateUI();

	}

	void GameStatePlaying::Shutdown()
	{
		
	}

	void GameStatePlaying::HandleWindowEvent(const sf::Event& event)
	{
		if (isGameOver) return;

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
		}
	}

	void GameStatePlaying::Update(float timeDelta, sf::RenderWindow& window)
	{
		if (isGameOver || isPaused) return;

		UpdatePlatformMovement(window);
		
		if (isBallLaunched)
		{
			UpdateBallMovement(timeDelta);
			CheckCollisions();
		}
	}

	void GameStatePlaying::Resume()
	{
		isPaused = false;
	}

	void GameStatePlaying::Draw(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(platform);
		window.draw(ball);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
		
		if (isGameOver)
		{
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setCharacterSize(48);
			gameOverText.setFillColor(sf::Color::Green);
			gameOverText.setString("GAME OVER");
			gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 0.5f }));
			gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEGHT / 2.f);
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
			score++;
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
		scoreText.setString("Score: " + std::to_string(score));
	}

	void GameStatePlaying::GameOver()
	{
		if (isGameOver) return;

		isGameOver = true;
		isBallLaunched = false;
		gameOverSound.play();

		m_game->UpdateRecord(PLAYER_NAME, score);
		m_game->SwitchStateTo(GameStateType::GameOver);
	}
}
