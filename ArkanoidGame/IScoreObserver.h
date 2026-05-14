#pragma once

namespace SnakeGame
{
	class IScoreObserver
	{
	public:
		virtual ~IScoreObserver() = default;
		virtual void OnScoreChanged(int newScore) = 0;
		virtual void OnBlockDestroyed(int points) = 0;
	};
}