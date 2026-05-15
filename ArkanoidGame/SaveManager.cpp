#include "SaveManager.h"

namespace SnakeGame
{
	void SaveManager::SaveState(std::unique_ptr<GameMemento> memento)
	{
		saveStack.push(std::move(memento));
	}

	std::unique_ptr<GameMemento> SaveManager::LoadLastState()
	{
		if (saveStack.empty())
		{
			return nullptr;
		}
		auto memento = std::move(saveStack.top());
		saveStack.pop();
		return memento;
	}

	bool SaveManager::HasSavedState() const
	{
		return !saveStack.empty();
	}

	void SaveManager::Clear()
	{
		while (!saveStack.empty())
		{
			saveStack.pop();
		}
	}
}