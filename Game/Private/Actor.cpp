#include "Game/Public/Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{

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

