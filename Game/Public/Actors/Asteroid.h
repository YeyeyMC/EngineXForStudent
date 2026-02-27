#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Asteroid : public Actor
{
public:
    Asteroid(float radius, exColor color);

    virtual void BeginPlay() override;
    virtual void Tick(const float DeltaSeconds) override;

    void SetVelocity(const exVector2& velocity);

private:
    void OnCollision(std::weak_ptr<Actor> other, const exVector2 hitLocation);

    float   mRadius;
    exColor mColor;
    bool mDead;
};
