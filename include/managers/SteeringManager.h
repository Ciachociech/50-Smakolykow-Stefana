#pragma once

#include "..\external_dependencies.h"

enum class keyAction{ none = 0, movingScene = 1, diggingScene, powerupUsingScene, mischievousCombo, anotherEvilCombo, steeringHelpScene, pauseScene, 
					enterMenu = 10, goBackMenu, prevMenu, nextMenu, lessMenu, moreMenu, 
					enterName = 20, backspaceName, acceptName, rejectName };

class SteeringManager
{
public:
	SteeringManager();
	virtual ~SteeringManager();

	//managing input from keyboard
	keyAction keyboardMovement(int& x, int& y, SDL_Keycode keycode);
	keyAction keyboardMenu(SDL_Keycode keycode);
	keyAction keyboardString(std::string& name, SDL_Event event);
private:
	int combo1, combo2;									//combo of performing bad actions

	void checkMischievousCombo(SDL_Keycode keycode);
	void checkAnotherEvilCombo(SDL_Keycode keycode);
};

