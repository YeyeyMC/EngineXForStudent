#include "Game/Public/Components/SquareRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void SquareRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		if (!mOwner.expired())
		{
			if (std::shared_ptr<Actor> owner = mOwner.lock())
			{
				if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
				{
					exVector2 CenterPos = TransformComp->GetLocation();
					exVector2 halfSize = { mWidth * 0.5f, mHeight * 0.5f };

					exVector2 p1 = { CenterPos.x - halfSize.x,CenterPos.y - halfSize.y };
					exVector2 p2 = { CenterPos.x + halfSize.x,CenterPos.y + halfSize.y };

					EngineInterface->DrawBox(p1, p2, mRenderColor, 1);
				}
			}
		}
	}
}

SquareRenderComponent::SquareRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float weight, float height)
	: RenderComponent(owner, RenderColor), mWidth(weight), mHeight(height)
{
}
