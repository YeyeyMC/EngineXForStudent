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
#include "Game/Public/Actors/Player.h"
#include "Game/Public/Actors/Ball.h"
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
	, mLeft( false )
	, mRight( false )
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
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mLeft = pState[SDL_SCANCODE_LEFT] || pState[SDL_SCANCODE_A];
	mRight = pState[SDL_SCANCODE_RIGHT] || pState[SDL_SCANCODE_D];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	if (mLeft && !mRight)
	{
		mPlayer->MoveLeft();
	}
	else if (mRight && !mLeft)
	{
		mPlayer->MoveRight();
	}
	else
	{
		mPlayer->StopMoving();
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
}
