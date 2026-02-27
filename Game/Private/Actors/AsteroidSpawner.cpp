#include "Game/Public/Actors/AsteroidSpawner.h"
#include "Game/Public/Actors/Asteroid.h"
#include "Engine/Public/EngineTypes.h"
#include <cstdlib>

static float RandRange(float minV, float maxV)
{
    const float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return minV + (maxV - minV) * t;
}

AsteroidSpawner::AsteroidSpawner(float spawnIntervalSeconds, int maxAlive, float minX, float maxX, float spawnY)
    : mSpawnInterval(spawnIntervalSeconds), mTimer(0.0f), mMaxAlive(maxAlive), mMinX(minX), mMaxX(maxX), mSpawnY(spawnY)
{
}

void AsteroidSpawner::BeginPlay()
{
    Actor::BeginPlay();
}

void AsteroidSpawner::Tick(const float DeltaSeconds)
{
    Actor::Tick(DeltaSeconds);

    mSpawned.erase(
        std::remove_if(mSpawned.begin(), mSpawned.end(),
            [this](const std::shared_ptr<Asteroid>& a)
            {
                if (!a) return true;

                if (a->IsDead()) return true;

                exVector2 p = a->GetComponentOfType<TransformComponent>()->GetLocation();

                return (p.x < mKillMinX || p.x > mKillMaxX || p.y < mKillMinY || p.y > mKillMaxY);
            }),
        mSpawned.end());

    if ((int)mSpawned.size() >= mMaxAlive) return;

    mTimer += DeltaSeconds;
    if (mTimer >= mSpawnInterval)
    {
        mTimer = 0.0f;
        SpawnOne();
    }
}

void AsteroidSpawner::SpawnOne()
{
    const float radius = RandRange(12.0f, 40.0f);

    exColor c;
    unsigned char g = (unsigned char)RandRange(90.0f, 160.0f);
    c.mColor[0] = g;
    c.mColor[1] = g;
    c.mColor[2] = g;
    c.mColor[3] = 255;

    exVector2 pos;
    pos.x = RandRange(mMinX, mMaxX);
    pos.y = mSpawnY;

    std::shared_ptr<Asteroid> a = Actor::SpawnActorOfType<Asteroid>(pos, radius, c);

    exVector2 v;
    v.x = RandRange(-0.3f, 0.3f);
    v.y = RandRange(0.8f, 2.2f);
    a->SetVelocity(v);

    mSpawned.push_back(a);
}
