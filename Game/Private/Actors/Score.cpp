#include "Game/Public/Actors/Score.h"
#include "Game/Public/Components/TextComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Utils.h"

Score::Score(int fontID)
	: mFontID(fontID)
	, mTextComponent(nullptr)
{
}

void Score::BeginPlay()
{
	Actor::BeginPlay();

	exColor ScoreColor;
	ScoreColor.mColor[0] = 255;
	ScoreColor.mColor[1] = 255;
	ScoreColor.mColor[2] = 255;
	ScoreColor.mColor[3] = 255;

	std::tuple<std::shared_ptr<TextComponent>, bool, String> ResultTextComponent =
		AddComponentOfType<TextComponent>("Score: 0", mFontID, ScoreColor);

	mTextComponent = std::get<0>(ResultTextComponent);
}

void Score::Tick(float DeltaTime)
{
	Actor::Tick(DeltaTime);

	if (mTextComponent)
	{
		if (exEngineInterface* Engine = AccessEngine())
		{
			mTextComponent->Render(Engine);
		}
	}
}

void Score::SetScoreText(const std::string& ScoreText)
{
	if (mTextComponent) mTextComponent->SetText(ScoreText);
}
