#pragma once
#include "Game/Public/Components/RenderComponent.h"

class SquareRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	SquareRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:

	SquareRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float width, float height);

private:

	float mHeight;
	float mWidth;
};
