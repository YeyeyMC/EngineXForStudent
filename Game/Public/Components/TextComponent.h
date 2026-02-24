#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include <string>
#include <memory>

class exEngineInterface;

class TextComponent : public Component
{
public:
	
	TextComponent() = delete;

	TextComponent(std::weak_ptr<Actor> Owner, const std::string& InitialText, int FontID, const exColor& TextColor);

	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;

	void SetText(const std::string& NewText);
	void SetColor(const exColor& NewColor);
	void SetFontID(int NewFontID);

	const std::string& GetText() const;

	virtual void Render(exEngineInterface* pEngine);

private:

	std::string mText;
	int mFontID;
	exColor mTextColor;
};