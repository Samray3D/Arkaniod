#pragma once
#include "GameMemento.h"
#include <stack>
#include <memory>

namespace SnakeGame
{
	class SaveManager
	{
	public:
		void SaveState(std::unique_ptr<GameMemento> memento);
		std::unique_ptr<GameMemento> LoadLastState();
		bool HasSavedState() const;
		void Clear();
	private:
		std::stack<std::unique_ptr<GameMemento>> saveStack;
	};
}