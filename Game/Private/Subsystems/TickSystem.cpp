#include "Game/Public/Actor.h"
#include "Game/Public/Subsystems/TickSystem.h"

std::unique_ptr<TickEngine> TickEngine::sTickEngine = nullptr;

TickEngine::TickEngine()
{
}

TickEngine::~TickEngine()
{
	ClearInvalidActor();
}

void TickEngine::AddActor(std::weak_ptr<Actor> actorToAdd)
{
	mActors.emplace_back(actorToAdd);
}

void TickEngine::ClearInvalidActor()
{
	if (mActors.empty()) {
		return;
	}
	mActors.remove_if(

		[](const std::weak_ptr<Actor>& component) {
			return component.expired();
		}
	);
}

void TickEngine::TickUpdate(const float DeltaSeconds)
{
	ClearInvalidActor();

	for (std::weak_ptr<Actor> Actor : mActors)
	{
		if (!Actor.expired())
		{
			Actor.lock()->Tick(DeltaSeconds);
		}
	}
}
