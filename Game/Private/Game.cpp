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
#include "Game/Public/Actors/Ball.h"
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
	, mUp( false )
	, mDown( false )
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

	float squareHeight = 300.0f;
	float squareWidth = 200.0f;

	float radius = 50.0f;
	float radius2 = 25.0f;

	exColor Color;
	Color.mColor[0] = 255;
	Color.mColor[1] = 50;
	Color.mColor[2] = 150;
	Color.mColor[3] = 255;

	exColor Color2;
	Color2.mColor[0] = 0;
	Color2.mColor[1] = 0;
	Color2.mColor[2] = 255;
	Color2.mColor[3] = 255;

	exColor Color3;
	Color3.mColor[0] = 255;
	Color3.mColor[1] = 150;
	Color3.mColor[2] = 0;
	Color3.mColor[3] = 255;

	//mBall = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 200.f), radius, Color);

	//mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 0.0f), radius2, Color2);

	/*if (std::shared_ptr<PhysicsComponent> BallPhysicsformComp = mBall_Second->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsformComp->SetVelocity(exVector2(0.0f, 0.5f));
	}*/

	mAsteroidSpawner = Actor::SpawnActorOfType<AsteroidSpawner>(exVector2(0.0f, 0.0f), 0.7f, 14, 20.0f, 780.0f, -60.0f);

	/*mBall = std::make_shared<Ball>(radius, Color);
	mBall->BeginPlay();*/

	/*mBall_Second = std::make_shared<Ball>(radius2, Color3);
	mBall_Second->BeginPlay();*/

	/*mSquare = std::make_shared<Square>(squareHeight, squareWidth, Color2);
	mSquare->BeginPlay();
	mSquare->AddComponentOfType<Component>();*/
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

	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	//mBall->Render(mEngine);
	//if (std::shared_ptr<RenderComponent> RenderComp = mBall->GetComponentOfType<RenderComponent>())
	//{
	//	RenderComp->Render(mEngine);
	//}
	//mBall->Tick(fDeltaT);
	//if (std::shared_ptr<RenderComponent> RenderComp = mBall_Second->GetComponentOfType<RenderComponent>())
	//{
	//	RenderComp->Render(mEngine);
	//}
	//mBall_Second->Tick(fDeltaT);
	/*if (std::shared_ptr<RenderComponent> RenderComp = mSquare->GetComponentOfType<RenderComponent>())
	{
		RenderComp->Render(mEngine);
	}*/
	exVector2 BallVelocity(0.0f, 0.0f);

	/*if (mUp)
	{
		BallVelocity.y = -2.5f;	
	}
	if (mDown)
	{
		BallVelocity.y = 2.5f;
	}
	if (std::shared_ptr<PhysicsComponent> BallPhysicsformComp = mBall->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsformComp->SetVelocity(BallVelocity);
	}*/
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	RENDER_ENGINE.RenderUpdate(mEngine);
	TICK_ENGINE.TickUpdate(fDeltaT);
}
