#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Utils.h"
#include "Game/Public/Actors/Asteroid.h"
#include "Game/Public/Actors/Score.h"


Ball::Ball(float BallRadius, exColor BallColor)
{
	mRadius = BallRadius;
	mColor = BallColor;
}


void Ball::BeginPlay()
{
	Actor::BeginPlay();
		
	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);
	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> ResultCircleCollider = AddComponentOfType<CircleColliderComponent>(mRadius+5.0);

	if (std::shared_ptr<CircleColliderComponent> CircleColliderComp = std::get<0>(ResultCircleCollider))
	{
		CircleColliderComp->SetIsTrigger(true);
		CircleColliderComp->SetLayer("Bullet");

		CollisionEventSignature CollisionDelegate = std::bind(&Ball::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		CircleColliderComp->ListenForCollision(CollisionDelegate);
	}
}

void Ball::OnCollision(std::weak_ptr<Actor> other, const exVector2)
{
	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>())
	{
		exColor Color;
		Color.mColor[0] = 20;
		Color.mColor[1] = 255;
		Color.mColor[2] = 120;
		Color.mColor[3] = 255;

		RenderComp->SetColor(Color);
	}

	auto otherShared = other.lock();
	if (!otherShared) return;

	if (std::dynamic_pointer_cast<Asteroid>(otherShared))
	{
		if (auto score = Score::GetActive().lock())
			score->AddScore(10);

		return;
	}
}

