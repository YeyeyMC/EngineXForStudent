#include "Game/Public/Actors/Asteroid.h"

#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/TransformComponent.h"

Asteroid::Asteroid(float radius, exColor color)
    : mRadius(radius)
    , mColor(color)
{
}

void Asteroid::BeginPlay()
{
    Actor::BeginPlay();

    AddComponentOfType<CircleRenderComponent>(mColor, mRadius);

    auto resultCollider = AddComponentOfType<CircleColliderComponent>(mRadius + 2.0f);
    if (std::shared_ptr<CircleColliderComponent> collider = std::get<0>(resultCollider))
    {
        CollisionEventSignature collisionDelegate = std::bind(&Asteroid::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
        collider->ListenForCollision(collisionDelegate);
    }

    AddComponentOfType<PhysicsComponent>(exVector2(0.0f, 1.0f), false, false);
}

void Asteroid::Tick(const float DeltaSeconds)
{
    Actor::Tick(DeltaSeconds);
}

void Asteroid::SetVelocity(const exVector2& velocity)
{
    if (std::shared_ptr<PhysicsComponent> phys = GetComponentOfType<PhysicsComponent>())
    {
        phys->SetVelocity(velocity);
    }
}

void Asteroid::OnCollision(std::weak_ptr<Actor> other, const exVector2 hitLocation)
{
    if (std::shared_ptr<RenderComponent> render = GetComponentOfType<RenderComponent>())
    {
        exColor c;
        c.mColor[0] = 255;
        c.mColor[1] = 120;
        c.mColor[2] = 80;
        c.mColor[3] = 255;
        render->SetColor(c);
    }

    // Destroy();
}
