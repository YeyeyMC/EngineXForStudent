#include "Game/Public/Subsystems/PhysycsSystem.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sPhysicsEngine = nullptr;

PhysicsEngine::~PhysicsEngine() {

	ClearInvalidPhysicscomponent();

}

void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponents.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicscomponent()
{
	if (mPhysicsComponents.empty()) {
		return;
	}
	mPhysicsComponents.remove_if(

		[](const std::weak_ptr<PhysicsComponent>& component) {
			return component.expired();
		}
	);
}

void PhysicsEngine::PhysicsUpdate(const float DeltaTime)
{
	ClearInvalidPhysicscomponent();
	for (size_t index1 = 0; index1 < mPhysicsComponents.size(); ++index1) {
		auto firstPhysicsComponentIt = mPhysicsComponents.begin();
		std::advance(firstPhysicsComponentIt, index1);

		if (!firstPhysicsComponentIt->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsComponentToCheck = firstPhysicsComponentIt->lock();
			for (size_t index2 = index1+1; index2 < mPhysicsComponents.size(); ++index2) 
			{
				auto secondPhysicsComponentIt = mPhysicsComponents.begin();
				std::advance(secondPhysicsComponentIt, index2);

				if (!secondPhysicsComponentIt->expired()) {
					std::shared_ptr<PhysicsComponent> secondPhysicsComponenttoCheck = secondPhysicsComponentIt->lock();
					if (firstPhysicsComponentToCheck->IsCollisionDetected(*secondPhysicsComponentIt)) {
						
						firstPhysicsComponentToCheck->BroadcastCollisionEvents(secondPhysicsComponenttoCheck->GetOwner(), {0.0f,0.0f});
						secondPhysicsComponenttoCheck->BroadcastCollisionEvents(firstPhysicsComponentToCheck->GetOwner(), {0.0f,0.0f});

						firstPhysicsComponentToCheck->CollisionResolution();
						secondPhysicsComponenttoCheck->CollisionResolution();

						secondPhysicsComponenttoCheck->DoPhysics();
					}
				}
			}

			firstPhysicsComponentToCheck->DoPhysics();
		}
	}
}

PhysicsEngine::PhysicsEngine() {

}
