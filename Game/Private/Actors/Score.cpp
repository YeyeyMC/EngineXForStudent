#include "Game/Public/Actors/Score.h"
#include "Game/Public/Components/TextComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Utils.h"

std::weak_ptr<Score> Score::sActiveScore;

Score::Score(int fontID)
	: mFontID(fontID)
	, mTextComponent(nullptr)
	, mScore(0)
{
}

Score::~Score()
{
	auto active = sActiveScore.lock();
	if (active.get() == this)
		sActiveScore.reset();
}

void Score::BeginPlay()
{
	Actor::BeginPlay();

	sActiveScore = std::dynamic_pointer_cast<Score>(shared_from_this());

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

int Score::GetScoreText()
{
	if (mTextComponent) return mScore;
}

void Score::AddScore(int points)
{
	mScore += points;

	SetScoreText("Score: " + std::to_string(mScore));
}

std::weak_ptr<Score> Score::GetActive()
{
	return sActiveScore;
}
