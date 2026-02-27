//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include <vector>
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysycsSystem.h"
#include "Game/Public/Subsystems/RenderingSystem.h"
#include "Game/Public/Subsystems/TickSystem.h"
#include "Game/Public/Actors/AsteroidSpawner.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "PG29 Yeison, Felipe, Vinicius";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
void MyGame::ChangeState(GameState newState)
{
	if (mState == newState) return;
	mState = newState;

}


void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont( "Resources/OpenSans.ttf", 32 );

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	float playerRadius = 30.0f;

	exColor PlayerColor;
	PlayerColor.mColor[0] = 255;
	PlayerColor.mColor[1] = 200;
	PlayerColor.mColor[2] = 0;
	PlayerColor.mColor[3] = 255;
	
	exVector2 PlayerStartPosition(350.0f, 550.0f);
	mPlayer = Actor::SpawnActorOfType<Player>(PlayerStartPosition, playerRadius, PlayerColor);

	mScore = Actor::SpawnActorOfType<Score>(exVector2(50.0f, 50.0f), mFontID);
	mAsteroidSpawner = Actor::SpawnActorOfType<AsteroidSpawner>(exVector2(0.0f, 0.0f), 0.7f, 14, 20.0f, 780.0f, -60.0f);

	mState = GameState::Playing;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	mInputSystem.Update();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------


void MyGame::Run(float fDeltaT)
{
	if (mState == GameState::Playing)
	{
		if (mInputSystem.IsMovingLeft() && !mInputSystem.IsMovingRight())
		{
			mPlayer->MoveLeft();
		}
		else if (mInputSystem.IsMovingRight() && !mInputSystem.IsMovingLeft())
		{
			mPlayer->MoveRight();
		}
		else
		{
			mPlayer->StopMoving();
		}

		if (mInputSystem.IsShootingPressed())
		{

		}

		PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
		RENDER_ENGINE.RenderUpdate(mEngine);
		TICK_ENGINE.TickUpdate(fDeltaT);


		if (mScore)
		{
			exVector2 posSubheader(250.0f, 300.0f);
			if (mScore->GetScoreText() == 100)
			{
				ChangeState(GameState::Win);
				return;
			}
		}

		if (mPlayer)
		{
			if (mPlayer->IsDead())
			{
				ChangeState(GameState::Lose);
				return;
			}
		}
	}
	else
	{
		exColor textColor;
		textColor.mColor[0] = 255;
		textColor.mColor[1] = 255;
		textColor.mColor[2] = 255;
		textColor.mColor[3] = 255;

		const char* message = (mState == GameState::Win) ? "YOU WIN!" : "GAME OVER";
		exVector2 posHearer(300.0f, 250.0f);
		exVector2 posSubheader(250.0f, 300.0f);
		mEngine->DrawText(mFontID, posHearer, message, textColor, 100);
		mEngine->DrawText(mFontID, posSubheader, "Press R to restart", textColor, 100);
		
		if (mInputSystem.IsRestartPressed()) 
		{

			Initialize(mEngine); // Reiniciar el juego
		}
		
	}
}
