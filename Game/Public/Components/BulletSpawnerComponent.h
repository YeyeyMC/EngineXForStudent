#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include <Game/Public/Actors/Ball.h>

class BulletSpawnerComponent : public Component
{
public:

	BulletSpawnerComponent() = delete;
	BulletSpawnerComponent(std::weak_ptr<Actor> owner, float spawnRate, float bulletSpeed);
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;
private:
	exVector2 mVelocity;
	float mSpawnRate;
	float bulletRadius;
	exColor Color;
	std::vector<std::shared_ptr<Ball>> mBullets;
	float mTimeSinceLastSpawn;

};

