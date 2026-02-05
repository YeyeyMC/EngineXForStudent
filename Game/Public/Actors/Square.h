#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Square : public Actor
{
public:

	Square(float Height, float Width, exColor BallColor);

	virtual void BeginPlay() override;

private:

	float mHeight;
	float mWidth;
	exColor mColor;
};