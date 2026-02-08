#pragma once
#include "Game/Public/Utils.h"

class exEngineInterface;
class Actor;

#define TICK_ENGINE TickEngine::GetInstance()

class TickEngine
{
public:

	~TickEngine();
	static TickEngine& GetInstance() {
		if (!sTickEngine)
		{
			sTickEngine.reset(new TickEngine());
		}
		return *sTickEngine;
	}

	void AddActor(std::weak_ptr<Actor> actorToAdd);
	void ClearInvalidActor();

	void TickUpdate(const float DeltaSeconds);


private:
	TickEngine();
	TickEngine(const TickEngine& OtherEngine) = delete;
	TickEngine& operator=(const TickEngine& OtherEngine) = delete;

	static std::unique_ptr<TickEngine> sTickEngine;

	std::list<std::weak_ptr<Actor>> mActors;
};
