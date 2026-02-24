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

void MyGame::Run( float fDeltaT )
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

	// @TODO: Implement shoot when IsShootingPressed() returns true
	if (mInputSystem.IsShootingPressed())
	{
		
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
}
