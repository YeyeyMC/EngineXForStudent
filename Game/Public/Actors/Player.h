#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Player : public Actor
{
public: 
	Player(float PlayerRadius, exColor PlayerColor);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnCollision(std::weak_ptr<Actor> OtherActor, const exVector2);
	void MoveLeft();
	void MoveRight();
	void StopMoving();

private:
	float mRadius;
	exColor mColor;
	float mSpeed;
	float mCurrentVelocity;
};
