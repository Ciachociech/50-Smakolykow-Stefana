#include "StefanManager.h"

StefanManager::StefanManager() : isMoving(false), destX(0), destY(0), attachedEffect(), effectStart(0), baseMotivation(0) {}

StefanManager::StefanManager(int baseMotivation) : isMoving(false), destX(0), destY(0), attachedEffect(), effectStart(0), baseMotivation(baseMotivation) {}

StefanManager::~StefanManager()
{
	attachedEffect.~Graph();
	stefan.~Stefan();
}

void StefanManager::setStefan(SDL_Renderer* renderer)
{
	if (baseMotivation > 0) { stefan = Stefan(584 + 32 * 10, 24 + 32 * 10, baseMotivation); }
	else { stefan = Stefan(584 + 32 * 10, 24 + 32 * 10); }
	stefan.loadFromFile(1.f, 1.f, 2, 2, "Assets/stefan_idle.png", renderer);
	attachedEffect = Graph(584 + 320, 24 + 320 - 16);
	attachedEffect.loadFromFile(1.f, 1.f, 4, 1, "Assets/confuse.png", renderer);
}

void StefanManager::moveStefan(int tileX, int tileY)
{
	bool boink = false;
	
	if (!isMoving)
	{
		destX = stefan.X() + 32 * tileX;
		destY = stefan.Y() + 32 * tileY;
		isMoving = true;
	}

	//Interaction with external walls
	if (stefan.X() == 584 && destX == 520) { destX = 584 + 32; boink = true; }
	else if (stefan.X() == 584 && destX == 552) { destX = 584; boink = true; }
	else if (stefan.X() == 1224 && destX == 1288) { destX = 1224 - 32; boink = true; }
	else if (stefan.X() == 1224 && destX == 1256) { destX = 1224; boink = true; }
	if (stefan.Y() == 24 && destY == -40) { destY = 24 + 32; boink = true; }
	else if (stefan.Y() == 24 && destY == -8) { destY = 24; boink = true; }
	else if (stefan.Y() == 664 && destY == 728) { destY = 664 - 32; boink = true; }
	else if (stefan.Y() == 664 && destY == 696) { destY = 664; boink = true; }

	//Interaction with internal walls
	//Axis X
	if ((stefan.Y() >= 184 && stefan.Y() <= 248) || (stefan.Y() >= 440 && stefan.Y() <= 504))
	{
		if (stefan.X() == 712 && destX == 776) { destX = 712 - 32; boink = true; }
		else if (stefan.X() == 712 && destX == 744) { destX = 712; boink = true; }
		if (stefan.X() == 840 && destX == 776) { destX = 840 + 32; boink = true; }
		else if (stefan.X() == 840 && destX == 808) { destX = 840; boink = true; }
		if (stefan.X() == 968 && destX == 1032) { destX = 968 - 32; boink = true; }
		else if (stefan.X() == 968 && destX == 1000) { destX = 968; boink = true; }
		if (stefan.X() == 1096 && destX == 1032) { destX = 1096 + 32; boink = true; }
		else if (stefan.X() == 1096 && destX == 1064) { destX = 1096; boink = true; }
	}
	//Axis Y
	if ((stefan.X() >= 744 && stefan.X() <= 808) || (stefan.X() >= 1000 && stefan.X() <= 1064))
	{
		if (stefan.Y() == 152 && destY == 216) { destY = 152 - 32; boink = true; }
		else if (stefan.Y() == 152 && destY == 184) { destY = 152; boink = true; }
		if (stefan.Y() == 280 && destY == 216) { destY = 280 + 32; boink = true; }
		else if (stefan.Y() == 280 && destY == 248) { destY = 280; boink = true; }
		if (stefan.Y() == 408 && destY == 472) { destY = 408 - 32; boink = true; }
		else if (stefan.Y() == 408 && destY == 440) { destY = 408; boink = true; }
		if (stefan.Y() == 536 && destY == 472) { destY = 536 + 32; boink = true; }
		else if (stefan.Y() == 536 && destY == 504) { destY = 536; boink = true; }
	}

	if (boink)
	{
		stefan.setConfusion(true);
		effectStart = SDL_GetTicks();
	}

	if (SDL_GetTicks() - effectStart >= 1000) { stefan.setConfusion(false); }

	if (!stefan.getConfusion())
	{
		if (stefan.X() > destX) { stefan.setXY(stefan.X() - 4, stefan.Y()); stefan.setSpriteSide(lookAt::left); }
		else if (stefan.X() < destX) { stefan.setXY(stefan.X() + 4, stefan.Y()); stefan.setSpriteSide(lookAt::right); }
		if (stefan.Y() > destY) { stefan.setXY(stefan.X(), stefan.Y() - 4); }
		else if (stefan.Y() < destY) { stefan.setXY(stefan.X(), stefan.Y() + 4); }
	}


	if (stefan.X() == destX && stefan.Y() == destY) { isMoving = false; }
	attachedEffect.setXY(stefan.X(), stefan.Y() - 16);
}

void StefanManager::render(SDL_Renderer* renderer)
{
	stefan.render(renderer);
	if (stefan.getConfusion()) { attachedEffect.render(renderer); }
}

Stefan StefanManager::getStefan() { return stefan; }

void StefanManager::reduceMotivation() { stefan.setMotivation(stefan.getMotivation() - 1); }

void StefanManager::setMotivation(int value) 
{
	baseMotivation = value;
	stefan.setMotivation(value);
}

void StefanManager::exterminate()
{
	stefan.free();
	attachedEffect.free();
	effectStart = 0;
}
