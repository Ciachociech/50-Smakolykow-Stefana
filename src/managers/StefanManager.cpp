#include "..\..\include\managers\StefanManager.h"

StefanManager::StefanManager() : isMoving(false), destX(0), destY(0), attachedEffect(), effectStart(0), stubborntunismStart(0), baseMotivation(0), am(NULL) {}

StefanManager::StefanManager(int baseMotivation) : isMoving(false), destX(0), destY(0), attachedEffect(), effectStart(0), stubborntunismStart(0), baseMotivation(baseMotivation), am(NULL) {}

StefanManager::~StefanManager()
{
	attachedEffect.~Graph();
	stefan.~Stefan();
}

//creates a representation of character and initialize its and attached effect
void StefanManager::setStefan(SDL_Renderer* renderer)
{
	//if base motivation is valid value, create a player object with initial coords
	if (baseMotivation > 0) { stefan = Stefan(584 + 32 * 10, 24 + 32 * 10, baseMotivation); }
	//otherwise also create it with initial coords, but without motivation value
	else { stefan = Stefan(584 + 32 * 10, 24 + 32 * 10); }
	destX = stefan.X(); destY = stefan.Y();														//prevent teleporting to previous coords (after losing)
	stefan.loadFromFile(1.f, 1.f, 2, 2, "Assets/characters/stefan_idle.png", renderer);			//load character texture from file
	attachedEffect = Graph(584 + 320, 24 + 320 - 16);											//create attached effect with initial coords
	attachedEffect.loadFromFile(1.f, 1.f, 4, 1, "Assets/characters/confuse.png", renderer);		//load effect texture from file
}

//Make a movement of main character
void StefanManager::moveStefan(int tileX, int tileY)
{
	bool bonk = false;													//flag to check a confusion invoking (when the wall is touched)
	
	//if player is not currently moving
	if (!isMoving)
	{
		destX = stefan.X() + 32 * tileX;
		destY = stefan.Y() + 32 * tileY;
		//if destination is different than current position, set moving flag to true
		if (tileX != 0 || tileY != 0) { isMoving = true; am->playEffect(AudioEffType::jump, -1); }
	}

	//Interaction with external walls
	if (stefan.X() == 584 && destX == 520) { destX = 584 + 32; bonk = true; }
	else if (stefan.X() == 584 && destX == 552) { destX = 584; bonk = true; }
	else if (stefan.X() == 1224 && destX == 1288) { destX = 1224 - 32; bonk = true; }
	else if (stefan.X() == 1224 && destX == 1256) { destX = 1224; bonk = true; }
	if (stefan.Y() == 24 && destY == -40) { destY = 24 + 32; bonk = true; }
	else if (stefan.Y() == 24 && destY == -8) { destY = 24; bonk = true; }
	else if (stefan.Y() == 664 && destY == 728) { destY = 664 - 32; bonk = true; }
	else if (stefan.Y() == 664 && destY == 696) { destY = 664; bonk = true; }

	//Interaction with internal walls
	//Axis X
	if ((stefan.Y() >= 184 && stefan.Y() <= 248) || (stefan.Y() >= 440 && stefan.Y() <= 504))
	{
		if (stefan.X() == 712 && destX == 776) { destX = 712 - 32; bonk = true; }
		else if (stefan.X() == 712 && destX == 744) { destX = 712; bonk = true; }
		if (stefan.X() == 840 && destX == 776) { destX = 840 + 32; bonk = true; }
		else if (stefan.X() == 840 && destX == 808) { destX = 840; bonk = true; }
		if (stefan.X() == 968 && destX == 1032) { destX = 968 - 32; bonk = true; }
		else if (stefan.X() == 968 && destX == 1000) { destX = 968; bonk = true; }
		if (stefan.X() == 1096 && destX == 1032) { destX = 1096 + 32; bonk = true; }
		else if (stefan.X() == 1096 && destX == 1064) { destX = 1096; bonk = true; }
	}
	//Axis Y
	if ((stefan.X() >= 744 && stefan.X() <= 808) || (stefan.X() >= 1000 && stefan.X() <= 1064))
	{
		if (stefan.Y() == 152 && destY == 216) { destY = 152 - 32; bonk = true; }
		else if (stefan.Y() == 152 && destY == 184) { destY = 152; bonk = true; }
		if (stefan.Y() == 280 && destY == 216) { destY = 280 + 32; bonk = true; }
		else if (stefan.Y() == 280 && destY == 248) { destY = 280; bonk = true; }
		if (stefan.Y() == 408 && destY == 472) { destY = 408 - 32; bonk = true; }
		else if (stefan.Y() == 408 && destY == 440) { destY = 408; bonk = true; }
		if (stefan.Y() == 536 && destY == 472) { destY = 536 + 32; bonk = true; }
		else if (stefan.Y() == 536 && destY == 504) { destY = 536; bonk = true; }
	}

	//If the collision with wall occured and when the stubbortunism is not active
	if (bonk && !isStubborntunismActive())
	{
		reduceMotivation(3);
		stefan.setConfusion(true);
		effectStart = SDL_GetTicks();
		am->stopChannel(-1);
		am->playEffect(AudioEffType::bonk, -1);
	}

	//turning off status conditions (1000 ms confusion and 200 ms walking break)
	if (stefan.getConfusion() && (SDL_GetTicks() - effectStart >= 1500)) { stefan.setConfusion(false); }
	else if (stefan.getWalkBreak() && (SDL_GetTicks() - effectStart >= 300)) { stefan.setWalkBreak(false); }

	//moving a character and changing the side of texture
	if (stefan.X() > destX) { stefan.setXY(stefan.X() - 4, stefan.Y()); stefan.setSpriteSide(lookAt::left); }
	else if (stefan.X() < destX) { stefan.setXY(stefan.X() + 4, stefan.Y()); stefan.setSpriteSide(lookAt::right); }
	if (stefan.Y() > destY) { stefan.setXY(stefan.X(), stefan.Y() - 4); }
	else if (stefan.Y() < destY) { stefan.setXY(stefan.X(), stefan.Y() + 4); }

	//if character is in its destination
	if (stefan.X() == destX && stefan.Y() == destY) 
	{ 
		//if character has been moving, make a short break
		if (isMoving) { stefan.setWalkBreak(true); effectStart = SDL_GetTicks(); }
		isMoving = false; 
	}
	attachedEffect.setXY(stefan.X(), stefan.Y() - 16);					//refresh effect coords
}

//render character and effect (if is needed)
void StefanManager::render(SDL_Renderer* renderer)
{
	stefan.render(renderer);
	//if effect is turned on
	if (stefan.getConfusion()) { attachedEffect.render(renderer); }
}

//return copy of object
Stefan StefanManager::getStefan() { return stefan; }

//substract a motivation by certain value
void StefanManager::reduceMotivation(int value) { stefan.setMotivation(stefan.getMotivation() - value); }

//set a BASE motivation for character
void StefanManager::setMotivation(int value) 
{
	baseMotivation = value;
	stefan.setBaseMotivation(value);
}

//count a percentage of left motivation
int StefanManager::getMotivationPercent() { return 100 * stefan.getMotivation() / stefan.getBaseMotivation(); }

//returns true when the stubborntunism counter is active (ability is going on)
bool StefanManager::isStubborntunismActive() { return stubborntunismStart != 0; }

//at the activation set timer to present tick, otherwise zeroes (deactivate) counter
void StefanManager::setStubborntunismActive(bool flag) 
{ 
	if (flag) { stubborntunismStart = SDL_GetTicks(); }  
	else { stubborntunismStart = 0; }
}

void StefanManager::appendAudioManager(AudioManager* am) { this->am = am; }

//delete character and effect objects
void StefanManager::exterminate()
{
	stefan.free();
	attachedEffect.free();
	effectStart = 0;
	stubborntunismStart = 0;
	am = NULL;
}
