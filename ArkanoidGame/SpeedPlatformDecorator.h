#pragma once
#include "PlatformDecorator.h"

namespace SnakeGame
{
	class SpeedPlatformDecorator : public PlatformDecorator
	{
	public:
		SpeedPlatformDecorator(std::unique_ptr<IPlatform> platform);
		void Update(float timeDelta) override;

	private:
		float originalSpeed;
		float boostedSpeed = 600.f;
		float timeRemaining = 8.f;
	};
}