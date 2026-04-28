#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Sprite.h"
#include "GameSettings.h"
#include "GameStateGameOver.h"
#include "GameStatePlaying.h"
#include "GameStateMainMenu.h"
#include "GameStatePauseMenu.h"
#include "GameStateRecords.h"
#include <unordered_map>


namespace SnakeGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		std::unique_ptr<GameStateData> data;
		bool isExclusivelyVisible = false;

		GameState() = default;
		GameState(GameStateType t, bool exclusive ) : type(t), isExclusivelyVisible(exclusive)
		{

		}
	};


	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta, sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		void PopState();

		void SwitchStateTo(GameStateType newState);

		GameOptions GetOptions() const { return options; }

		void SetWindow(sf::RenderWindow* window) { m_window = window; }
		sf::RenderWindow* GetWindow() { return m_window; }

	private:
		sf::RenderWindow* m_window = nullptr;

		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;

		void InitGameState(GameState& state);
		void ShutdownGameState(GameState& state);

		void UpdateGameState(GameState& state, float timeDelta, sf::RenderWindow& window);
		void DrawGameState(GameState& state, sf::RenderWindow& window);

		std::unique_ptr<GameStateData> CreateGameState(GameStateType type);
	};
}
