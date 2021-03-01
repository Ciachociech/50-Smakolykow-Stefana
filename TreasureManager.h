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
	int returnGatheredScore();

	bool checkTile(int x, int y);

	void exterminate();
private:
	
	//structure for relating a tile with certain treasure
	struct CoordsPair
	{
		CoordsPair(int x, int y, int ID) : x(x), y(y), objectID(ID) {}
		int x;
		int y;
		int objectID;
	};
	typedef std::vector<CoordsPair> VecPair;
	
	VecTreasures treasures;									//vector of Treasure objects (for treasures on scene)
	VecGraph minis;											//vector of Graph objects (for miniatures on UI)
	int count;												//number of treasure on map
	OverworldRandomizer overand;							//randomizer
	int framesLeft, treasuresLeft, gatheredScore;			//frames and treasures left to find and score to add during frame
	VecPair pairs;											//vector of CoordsPair objects

	treasureType randomizeType(int& tileW, int& tileH);
};

