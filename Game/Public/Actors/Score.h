#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>

class TextComponent;

class Score : public Actor
{
public:

	Score(int fontID);
	~Score();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetScoreText(const std::string& ScoreText);
	int GetScoreText();
	void AddScore(int points);

	static std::weak_ptr<Score> GetActive();
private:

	int mFontID;
	int mScore;
	std::shared_ptr<TextComponent> mTextComponent;
	static std::weak_ptr<Score> sActiveScore;
};