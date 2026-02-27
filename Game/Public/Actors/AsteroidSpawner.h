#pragma once
#include "Game/Public/Actor.h"
#include <vector>
#include <memory>

class Asteroid;

class AsteroidSpawner : public Actor
{
public:
    AsteroidSpawner(float spawnIntervalSeconds = 0.8f, int maxAlive = 12, float minX = 0.0f, float maxX = 800.0f, float spawnY = -50.0f);

    virtual void BeginPlay() override;
    virtual void Tick(const float DeltaSeconds) override;

private:
    void SpawnOne();

private:
    float mSpawnInterval;
    float mTimer;

    int mMaxAlive;

    float mMinX;
    float mMaxX;
    float mSpawnY;

    float mKillMinX = -100.0f;
    float mKillMaxX = 1380.0f;
    float mKillMinY = -100.0f;
    float mKillMaxY = 820.0f;

    std::vector<std::shared_ptr<Asteroid>> mSpawned;
};
