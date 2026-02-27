#include "Game/Public/Components/BulletSpawnerComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"

BulletSpawnerComponent::BulletSpawnerComponent(std::weak_ptr<Actor> owner, float spawnRate, float bulletSpeed) :
	Component(owner), mSpawnRate(spawnRate)
{
	mVelocity = { 0.0f, -bulletSpeed };
	bulletRadius = 5.0f;

	Color.mColor[0] = 255;
	Color.mColor[1] = 50;
	Color.mColor[2] = 150;
	Color.mColor[3] = 255;

	mTimeSinceLastSpawn = 0.0f;
	
}

void BulletSpawnerComponent::BeginPlay()
{
	Component::BeginPlay();
	
}

void BulletSpawnerComponent::Tick(const float DeltaTime)
{
	mTimeSinceLastSpawn += DeltaTime;
	if (mTimeSinceLastSpawn >= mSpawnRate) {

		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>()) 
		{		
			std::shared_ptr<Ball> newBullet = Actor::SpawnActorOfType<Ball>(exVector2(TransformComp->GetLocation().x, TransformComp->GetLocation().y - 50), bulletRadius, Color);
			//newBullet->GetComponentOfType<PhysicsComponent>()->SetLayer("Bullet");
			if (std::shared_ptr<PhysicsComponent> BulletPhysicsformComp = newBullet->GetComponentOfType<PhysicsComponent>())
			{
				BulletPhysicsformComp->SetVelocity(mVelocity);
			}
			mBullets.emplace_back(newBullet);
			mTimeSinceLastSpawn = 0.0f;
		}
	}
	 auto it = std::remove_if(mBullets.begin(), mBullets.end(),
	 	[](const std::shared_ptr<Ball>& b) {
	 		if (!b) return true;
	 		if (auto t = b->GetComponentOfType<TransformComponent>()) {
	 			return t->GetLocation().y < -1000.0f; // criterio de eliminación
	 		}
	 		return false;
	 	});
	 mBullets.erase(it, mBullets.end());
}

