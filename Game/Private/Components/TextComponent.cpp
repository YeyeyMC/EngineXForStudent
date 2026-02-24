#include "Game/Public/Components/TextComponent.h"
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineInterface.h"

TextComponent::TextComponent(std::weak_ptr<Actor> Owner, const std::string& InitialText, int FontID, const exColor& TextColor)
	: Component(Owner)
	, mText(InitialText)
	, mFontID(FontID)
	, mTextColor(TextColor)
{
}

void TextComponent::BeginPlay()
{
	Component::BeginPlay();
}

void TextComponent::Tick(const float DeltaTime)
{
	Component::Tick(DeltaTime);
}

void TextComponent::SetText(const std::string& NewText)
{
	mText = NewText;
}

const std::string& TextComponent::GetText() const
{
	return mText;
}

void TextComponent::SetColor(const exColor& NewColor)
{
	mTextColor = NewColor;
}

void TextComponent::SetFontID(int NewFontID)
{
	mFontID = NewFontID;
}

void TextComponent::Render(exEngineInterface* pEngine)
{
	if (!pEngine || mFontID < 0)
	{
		return;
	}

	if (std::shared_ptr<Actor> OwnerActor = GetOwner().lock())
	{
		if (std::shared_ptr<TransformComponent> Transform = OwnerActor->GetComponentOfType<TransformComponent>())
		{
			exVector2 Position = Transform->GetLocation();  
			pEngine->DrawText(mFontID, Position, mText.c_str(), mTextColor, 0);
		}
	}
}