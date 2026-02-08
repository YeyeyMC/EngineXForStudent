#include "Game/Public/Actor.h"
#include "Game/Public/Subsystems/TickSystem.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	TICK_ENGINE.AddActor(weak_from_this());
}

void Actor::EndPlay()
{
	// TODO
}

void Actor::Tick(const float DeltaSeconds)
{
	// TODO
	for (std::shared_ptr<Component> ComponentIt : mComponents) {
		ComponentIt->Tick(DeltaSeconds);
	}
}

