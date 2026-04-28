#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "Text.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateData.h"

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

	std::unique_ptr<GameStateData> Game::CreateGameState(GameStateType type)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
			return std::make_unique<GameStateMainMenu>();
		case GameStateType::Playing:
			return std::make_unique<GameStatePlaying>();
		case GameStateType::GameOver:
			return std::make_unique<GameStateGameOver>();
		case GameStateType::ExitDialog:
			return std::make_unique<GameStatePauseMenu>();
		case GameStateType::Records:
			return std::make_unique<GameStateRecords>();
		default:
			return nullptr;
		}
	}

	void Game::InitGameState(GameState& state)
	{
		state.data = CreateGameState(state.type);
		if (state.data)
		{
			state.data->Init(this);
		}
	}

	void Game::ShutdownGameState(GameState& state)
	{
		if (state.data)
		{
			state.data.reset();
		}
		state.type = GameStateType::None;
	}

	void Game::UpdateGameState(GameState& state, float timeDelta, sf::RenderWindow& window)
	{
		if (state.data)
		{
			if (state.type == GameStateType::Playing)
			{
				static_cast<GameStatePlaying*>(state.data.get())->Update(timeDelta, window);
			}
			else
			{
				state.data->Update(timeDelta);
			}
		}
	}

	void Game::DrawGameState(GameState& state, sf::RenderWindow& window)
	{
		if (state.data)
		{
			state.data->Draw(window);
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
			if (stateStack.size() > 0 && stateStack.back().data)
			{
				stateStack.back().data->HandleWindowEvent(event);
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
					stateStack.back().data->Resume();
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
