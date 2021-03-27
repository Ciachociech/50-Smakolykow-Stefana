#pragma once

#include "external_dependencies.h"

#include "OverworldRandomizer.h"
#include "Treasure.h"

enum class PowerupStatus { none = 0, covered = 1, discovered, avaiable, used };

typedef std::vector<std::unique_ptr<Treasure>> VecTreasures;

class TreasureManager
{
public:
	TreasureManager();
	~TreasureManager();

	void randomizeTreasures(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void renderIndicator(SDL_Renderer* renderer);

	int getCount();
	int getFramesLeft();
	int getTreasuresLeft();
	int returnGatheredScore();
	int getMotivationCompensation();
	PowerupStatus getPowerupStatus();
	treasureType getPowerupType();

	void setPowerupStatus(PowerupStatus pupStat, SDL_Renderer* renderer);
	void showRandomTile(SDL_Renderer* renderer);

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
	Treasure powerup, powerupIconUI;						//treasure object being a powerup (one of 3 avaiable)
	PowerupStatus powerupStatus;							//treasure object state
	Graph powerupStar, scanIndicator;						//indicator used with nosescan ability
	bool showScanIndicator = false;							//flag for showing nosescan's ability
	int count;												//number of treasure on map
	OverworldRandomizer overand;							//randomizer
	int framesLeft, treasuresLeft, gatheredScore;			//frames and treasures left to find and score to add during frame
	VecPair pairs;											//vector of CoordsPair objects
	int motivationCompensation;								//number of additional compensation of harder tidbits

	treasureType randomizeType(int& tileW, int& tileH);
	treasureType randomizePowerup();
};

