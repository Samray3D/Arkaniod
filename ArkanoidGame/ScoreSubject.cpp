#include "ScoreSubject.h"
#include <algorithm>

namespace SnakeGame
{
	void ScoreSubject::AddObserver(IScoreObserver* observer)
	{
		observers.push_back(observer);
	}

	void ScoreSubject::RemoveObserver(IScoreObserver* observer)
	{
		auto it = std::remove(observers.begin(), observers.end(), observer);
		observers.erase(it, observers.end());
	}

	void ScoreSubject::NotifyScoreChanged(int newScore)
	{
		for (auto observer : observers)
		{
			observer->OnScoreChanged(newScore);
		}
	}

	void ScoreSubject::NotifyBlockDestroyed(int points)
	{
		for (auto observer : observers)
		{
			observer->OnBlockDestroyed(points);
		}
	}
}