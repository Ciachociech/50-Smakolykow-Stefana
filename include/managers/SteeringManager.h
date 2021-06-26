#pragma once

#include "..\external_dependencies.h"

enum class keyAction { none = 0, moving = 1, digging, powerupUsing, mischievous, anotherEvil, steeringHelp, pause, enter = 10, goBack, prev, next, less, more };

class SteeringManager
{
public:
	SteeringManager();
	virtual ~SteeringManager();

	keyAction keyboardMovement(int& x, int& y, SDL_Keycode keycode);
	keyAction keyboardMenu(SDL_Keycode keycode);
private:
	int combo1, combo2;									//combo of performing bad actions

	void checkMischievousCombo(SDL_Keycode keycode);
	void checkAnotherEvilCombo(SDL_Keycode keycode);
};

