#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "Text.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace SnakeGame
{
	const char* PLAYER_NAME = "Player";
	Game::Game()
	{
	
		recordsTable =
		{
			{"John", MAX_APPLES / 2},
			{"Jane", MAX_APPLES / 3 },
			{"Alice", MAX_APPLES / 4 },
			{"Bob", MAX_APPLES / 5 },
			{"Clementine", MAX_APPLES / 5 },
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::InitGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			new (&state.data.mainMenu) GameStateMainMenu();
			state.data.mainMenu.Init(this);
			break;
		}
		case GameStateType::Playing:
		{
			new (&state.data.playing) GameStatePlaying();
			state.data.playing.Init(this);
			break;
		}
		case GameStateType::GameOver:
		{
			new (&state.data.gameOver) GameStateGameOver();
			state.data.gameOver.Init(this);
			break;
		}
		case GameStateType::ExitDialog:
		{
			new (&state.data.pauseMenu) GameStatePauseMenu();
			state.data.pauseMenu.Init(this);
			break;
		}
		case GameStateType::Records:
		{
			new (&state.data.records) GameStateRecords();
			state.data.records.Init(this);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Game::ShutdownGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data.mainMenu.Shutdown();
			state.data.mainMenu.~GameStateMainMenu();
			break;
		}
		case GameStateType::Playing:
		{
			state.data.playing.Shutdown();
			state.data.playing.~GameStatePlaying();
			break;
		}
		case GameStateType::GameOver:
		{
			state.data.gameOver.Shutdown();
			state.data.gameOver.~GameStateGameOver();
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data.pauseMenu.Shutdown();
			state.data.pauseMenu.~GameStatePauseMenu();
			break;
		}
		case GameStateType::Records:
		{
			state.data.records.Shutdown();
			state.data.records.~GameStateRecords();
			break;
		}
		default:
			assert(false);
			break;
		}
		state.type = GameStateType::None;
	}

	void Game::HandleWindowEventGameState(GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data.mainMenu.HandleWindowEvent(event);
			break;
		}
		case GameStateType::Playing:
		{
			state.data.playing.HandleWindowEvent(event);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data.gameOver.HandleWindowEvent(event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data.pauseMenu.HandleWindowEvent(event);
			break;
		}
		case GameStateType::Records:
		{
			state.data.records.HandleWindowEvent(event);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Game::UpdateGameState(GameState& state, float timeDelta, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data.mainMenu.Update(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			state.data.playing.Update(timeDelta, window);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data.gameOver.Update(timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data.pauseMenu.Update(timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			state.data.records.Update(timeDelta);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Game::DrawGameState(GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data.mainMenu.Draw(window);
			break;
		}
		case GameStateType::Playing:
		{
			state.data.playing.Draw(window);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data.gameOver.Draw(window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data.pauseMenu.Draw(window);
			break;
		}
		case GameStateType::Records:
		{
			state.data.records.Draw(window);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				HandleWindowEventGameState(stateStack.back(), event);
			}
		}
	}

	bool Game::Update(float timeDelta, sf::RenderWindow& window)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			while (stateStack.size() > 0)
			{
				ShutdownGameState(stateStack.back());
				stateStack.pop_back();
			}
			stateChangeType = GameStateChangeType::None;
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			if (stateStack.size() > 0)
			{
				ShutdownGameState(stateStack.back());
				stateStack.pop_back();
				if (stateStack.size() > 0 && stateStack.back().type == GameStateType::Playing)
				{
					stateStack.back().data.playing.Resume();
				}

			}
			stateChangeType = GameStateChangeType::None;
		}

		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.emplace_back(pendingGameStateType, pendingGameStateIsExclusivelyVisible);
			InitGameState(stateStack.back());
			pendingGameStateType = GameStateType::None;
			pendingGameStateIsExclusivelyVisible = false;
		}

		if (stateStack.size() > 0)
		{
			UpdateGameState(stateStack.back(), timeDelta, window);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(**it, window);
			}
		}
	}

	void Game::Shutdown()
	{
		while (stateStack.size() > 0)
		{
			ShutdownGameState(stateStack.back());
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		return (static_cast<uint8_t>(options) & static_cast<uint8_t>(option)) != 0;
	}
	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = static_cast<GameOptions>(static_cast<uint8_t>(options) | static_cast<uint8_t>(option));
		}
		else
		{
			options = static_cast<GameOptions>(static_cast<uint8_t>(options) & ~static_cast<uint8_t>(option));
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		if (it != recordsTable.end())
		{
			return it->second;
		}
		return 0;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		auto it = recordsTable.find(playerId);
		if (it != recordsTable.end())
		{
			if (score > it->second)
			{
				it->second = score;
			}
		}
		else if (recordsTable.size() < MAX_RECORDS_TABLE_SIZE)
		{
			recordsTable[playerId] = score;
		}
	}
			
}
