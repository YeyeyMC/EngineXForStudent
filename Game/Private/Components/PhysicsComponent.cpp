#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Subsystems/PhysycsSystem.h"
#include "Game/Public/Actor.h"

PhysicsComponent::PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity, 
                                    bool isStatic, bool isGravityEnabled, bool isTrigger, String layer): Component(owner), 
                                    mVelocity(velocity), mIsStatic(isStatic), mIsGravityEnabled(isGravityEnabled),
                                    mIsTrigger(isTrigger), mLayer(layer)
{
}

void PhysicsComponent::BeginPlay()
{
    Component::BeginPlay();

    PHYSICS_ENGINE.AddPhysicsComponent(weak_from_this());
}

void PhysicsComponent::Tick(const float DeltaTime)
{
    //DoPhysics();
}

void PhysicsComponent::DoPhysics()
{

    if (mIsStatic) {
        return;
    }
    if (mOwner.expired()) {
        return;
    }
    if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>()) {
        exVector2 NewPosition = TransformComp->GetLocation() + mVelocity;
        TransformComp->SetLocation(NewPosition);
    }
}

bool PhysicsComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
    return false;
}

void PhysicsComponent::CollisionResolution()
{
}

void PhysicsComponent::ListenForCollision(CollisionEventSignature& delegateToAdd)
{
    mCollisionEvents.emplace_back(delegateToAdd);
}

void PhysicsComponent::StopListeningForCollision(CollisionEventSignature& delegateToRemove)
{

    mCollisionEvents.remove_if(
        [&delegateToRemove](const CollisionEventSignature& Event) {

            return &Event == &delegateToRemove;
        }
    );
}

void PhysicsComponent::BroadcastCollisionEvents(std::weak_ptr<Actor> otherActor, exVector2 hitLocation)
{
    for (CollisionEventSignature& Event : mCollisionEvents) {
        Event(otherActor, hitLocation);
    }
}

exVector2 PhysicsComponent::GetVelocity() const
{
    return mVelocity;
}

void PhysicsComponent::SetVelocity(exVector2 inVelocity)
{
    mVelocity = inVelocity;
}

bool PhysicsComponent::IsTrigger() const
{
    return mIsTrigger;
}

void PhysicsComponent::SetIsTrigger(bool value)
{
    mIsTrigger = value;
}

String PhysicsComponent::GetLayer() const
{
    return mLayer;
}

void PhysicsComponent::SetLayer(String layer)
{
    mLayer = layer;
}
