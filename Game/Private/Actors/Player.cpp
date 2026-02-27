#include "Game/Public/Actors/Player.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Utils.h"
#include "Game/Public/Components/BulletSpawnerComponent.h"

Player::Player(float PlayerRadius, exColor PlayerColor)
	: mSpeed(2.0f)
	, mCurrentVelocity(0.0f)
{
	mRadius = PlayerRadius;
	mColor = PlayerColor;
}


void Player::BeginPlay()
{
	Actor::BeginPlay();

	AddComponentOfType<BulletSpawnerComponent>(0.5f, 10.0f);

	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);

	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> ResultCircleCollider = AddComponentOfType<CircleColliderComponent>(mRadius + 5.0);

	if (std::shared_ptr<CircleColliderComponent> CircleColliderComp = std::get<0>(ResultCircleCollider))
	{
		CircleColliderComp->SetIsTrigger(true);
		CircleColliderComp->SetLayer("Player");

		CollisionEventSignature CollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		CircleColliderComp->ListenForCollision(CollisionDelegate);
	}
}

#include "Engine/Public/EngineInterface.h"

void Player::Tick(float DeltaTime)
{
	Actor::Tick(DeltaTime);

	if (std::shared_ptr<PhysicsComponent> PlayerPhysics = GetComponentOfType<PhysicsComponent>())
	{
		PlayerPhysics->SetVelocity(exVector2(mCurrentVelocity, 0.0f));
	}

	if (std::shared_ptr<TransformComponent> Transform = GetComponentOfType<TransformComponent>())
	{
		exVector2 CurrentPos = Transform->GetLocation();

		float MinX = mRadius;
		float MaxX = kViewportWidth - mRadius;

		if (CurrentPos.x < MinX)
		{
			CurrentPos.x = MinX;
			Transform->SetLocation(CurrentPos);
		}
		else if (CurrentPos.x > MaxX)
		{
			CurrentPos.x = MaxX;
			Transform->SetLocation(CurrentPos);
		}
	}
}

void Player::OnCollision(std::weak_ptr<Actor> OtherActor, const exVector2 HitLocation)
{
	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>())
	{
		exColor Color;
		Color.mColor[0] = 255;
		Color.mColor[1] = 0;
		Color.mColor[2] = 0;
		Color.mColor[3] = 255;

		RenderComp->SetColor(Color);
		Kill();
	}
}

void Player::MoveLeft()
{
	mCurrentVelocity = -mSpeed;
}

void Player::MoveRight()
{
	mCurrentVelocity = mSpeed;
}

void Player::StopMoving()
{
	mCurrentVelocity = 0.0f;
}