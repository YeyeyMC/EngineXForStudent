//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//
#pragma once

#include "Game/Public/Utils.h"
#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Actors/Player.h"
#include "Game/Public/Actors/Square.h"
#include "Game/Public/InputSystem.h"
#include "Game/Public/Actors/AsteroidSpawner.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	InputSystem					mInputSystem;

	bool						mLeft;
	bool						mRight;

	exVector2					mTextPosition;
	std::shared_ptr<Player>        mPlayer;
	std::shared_ptr<AsteroidSpawner> mAsteroidSpawner;
};
