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
	int getTreasuresLeft();

	bool checkTile(int x, int y);

	void exterminate();
private:
	
	struct CoordsPair
	{
		CoordsPair(int x, int y, int ID) : x(x), y(y), objectID(ID) {}
		int x;
		int y;
		int objectID;
	};
	typedef std::vector<CoordsPair> VecPair;
	
	VecTreasures treasures;
	VecGraph minis;
	int count;
	OverworldRandomizer overand;
	int framesLeft, treasuresLeft;
	VecPair pairs;

	treasureType randomizeType();
};

