#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>

class TextComponent;

class Score : public Actor
{
public:

	Score(int fontID);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetScoreText(const std::string& ScoreText);

private:

	int mFontID;
	std::shared_ptr<TextComponent> mTextComponent;
};