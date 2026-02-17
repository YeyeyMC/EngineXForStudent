#include "Game/Public/InputSystem.h"
#include "Engine/Public/SDL.h"

InputSystem::InputSystem()
	: mLeft(false)
	, mRight(false)
	, mShoot(false)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Update()
{
	int nKeys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&nKeys);

	mLeft = pState[SDL_SCANCODE_LEFT] || pState[SDL_SCANCODE_A];
	mRight = pState[SDL_SCANCODE_RIGHT] || pState[SDL_SCANCODE_D];

	// @TODO Implement shoot when the space key is pressed
}

bool InputSystem::IsMovingLeft() const
{
	return mLeft;
}

bool InputSystem::IsMovingRight() const
{
	return mRight;
}

bool InputSystem::IsShootingPressed() const
{
	// @TODO Implement shoot when the space key is pressed
	return mShoot;
}