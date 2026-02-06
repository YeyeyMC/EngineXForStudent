#include "Game/Public/Subsystems/RenderingSystem.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr<RenderEngine> RenderEngine::sRenderEngine = nullptr;

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
	ClearInvalidRenderComponent();
}

void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponent()
{
	if (mRenderComponents.empty()) {
		return;
	}
	mRenderComponents.remove_if(

		[](const std::weak_ptr<RenderComponent>& component) {
			return component.expired();
		}
	);
}

void RenderEngine::RenderUpdate(exEngineInterface* RenderInterface)
{
	ClearInvalidRenderComponent();

	for (std::weak_ptr<RenderComponent> RenderComponent : mRenderComponents)
	{
		if (!RenderComponent.expired())
		{
			RenderComponent.lock()->Render(RenderInterface);
		}
	}
}
