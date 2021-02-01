#pragma once

#include "external_dependencies.h"

#include "OverworldRandomizer.h"
#include "Treasure.h"

typedef std::vector<std::unique_ptr<Treasure>> VecTreasures;

class TreasureManager
{
public:
	TreasureManager();
	~TreasureManager();

	void randomizeTreasures(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);

	int getCount();
	int getFramesLeft();
	bool checkTile(int x, int y);

	void exterminate();
private:
	
	struct CoordsPair
	{
		CoordsPair(int x, int y) : x(x), y(y) {}
		int x;
		int y;
	};
	typedef std::vector<CoordsPair> VecPair;
	
	VecTreasures treasures;
	int count;
	OverworldRandomizer overand;
	int framesLeft;
	VecPair pairs;

	treasureType randomizeType();
};

