#pragma once
#include "Stefan.h"

class StefanManager
{
public:
	StefanManager();
	StefanManager(int baseMotivation);
	virtual ~StefanManager();

	void setStefan(SDL_Renderer* renderer);
	void moveStefan(int tileX, int tileY);

	void render(SDL_Renderer* renderer);
	Stefan getStefan();
	void reduceMotivation();
	void setMotivation(int value);

	void exterminate();
private:
	Stefan stefan;
	Graph attachedEffect;
	bool isMoving;
	int destX, destY;
	Uint32 effectStart;
	int baseMotivation;
};