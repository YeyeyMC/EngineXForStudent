#pragma once

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void Update();

	bool IsMovingLeft() const;
	bool IsMovingRight() const;
	bool IsRestartPressed() const;

	bool IsShootingPressed() const;

private:
	bool mLeft;
	bool mRight;
	bool mShoot;
	bool mRestart;
};