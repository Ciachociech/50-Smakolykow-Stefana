#pragma once
#include "Stefan.h"
#include "AudioManager.h"

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
	void reduceMotivation(int value = 1);
	void setMotivation(int value);
	int getMotivationPercent();
	bool isStubborntunismActive();
	void setStubborntunismActive(bool flag = true);
	void appendAudioManager(AudioManager* am);

	void exterminate();
private:
	Stefan stefan;												//character object
	Graph attachedEffect;										//effect of confusion
	bool isMoving;												//flag is true when the player does not reach its destination, otherwise is false
	int destX, destY;											//coords of destination
	Uint32 effectStart, stubborntunismStart;					//time counter for start of effect or stubburtonism
	int baseMotivation;											//base motivation of level
	AudioManager* am;											//attached audio manager (it's simplier to add this instead of returning state)
};