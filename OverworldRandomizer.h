#pragma once
#include "external_dependencies.h"

class OverworldRandomizer
{
public:
	OverworldRandomizer();
	virtual ~OverworldRandomizer();
	SDL_Color randomColor();
	int randomNumber(int min, int max);
	void randomCoordsTreasure(int& x, int& y);
private:
	std::default_random_engine gen;
}; 

