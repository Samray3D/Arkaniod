#pragma once
#include <vector>
#include "IScoreObserver.h"

namespace SnakeGame
{
	class ScoreSubject
	{
	public:
		void AddObserver(IScoreObserver* observer);
		void RemoveObserver(IScoreObserver* observer);
		void NotifyScoreChanged(int newScore);
		void NotifyBlockDestroyed(int points);

	private:
		std::vector<IScoreObserver*> observers;
	};
}