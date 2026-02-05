#include "Game/Public/Actors/Square.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/SquareRenderComponent.h"

Square::Square(float Height, float Width, exColor BallColor)
{
	mHeight = Height;
	mWidth = Width;
	mColor = BallColor;
}


void Square::BeginPlay()
{
	AddComponentOfType<TransformComponent>(exVector2{ 500.0f, 500.0f });
	AddComponentOfType<SquareRenderComponent>(mColor, mWidth, mHeight);
}

