#include "..\..\include\managers\TreasureManager.h"

TreasureManager::TreasureManager() : overand(), treasures(), count(0), framesLeft(0), treasuresLeft(0), gatheredScore(0), motivationCompensation(0), pairs(), powerup(treasureType::none), powerupStatus(PowerupStatus::none), powerupIconUI(treasureType::none) {}

TreasureManager::~TreasureManager() { treasures.~vector(); pairs.~vector(); }

//randomize a type and position of treasures on the level
void TreasureManager::randomizeTreasures(SDL_Renderer* renderer)
{
	//tresaure management
	this->count = overand.randomNumber(4, 5);				//set a number of treasures (tidbits)

	//for each treasure
	for (int i = 0; i < this->count; i++) 
	{
		int x, y, tileW, tileH;								//information about coords and tile dimensions
		bool isHere;										//flag with treasure validitation, true value force a next randomizing
		treasureType tType;									//contains information about treasure type

		//do until position is valid with another treasures (each other)
		do
		{
			//initalize values
			x = 0, y = 0, tileW = 0, tileH = 0;	
			isHere = false;

			//randomize type and position of treasure
			tType = randomizeType(tileW, tileH);
			overand.randomCoordsTreasure(x, y, tileW, tileH);

			//prevention of setting treasures close to or one on another (making at least one tile width and height free space)
			//for each treasure already created (not this which is creating)
			for (int j = 0; j < treasures.size(); j++)
			{
				//if current position is too close previous position of treasure, change a randomizing flag to true
				if (((x + 32 * tileW + 32) > (treasures[j]->X() - 32)) && ((treasures[j]->X() + treasures[j]->W() + 32) > (x - 32)) 
					&& ((y + 32 * tileH + 32) > (treasures[j]->Y() - 32)) && ((treasures[j]->Y() + treasures[j]->H() + 32) > (y - 32))) { isHere = true; }
			}
		} while (isHere);
		
		//make a new treasure and get path with randomize position
		treasures.push_back(std::make_unique<Treasure>(tType));
		treasures.back()->loadFromFile(1.f, 1.f, "Assets/scene/" + treasures.back()->getAssetPath(), renderer);
		treasures.back()->setXY(x, y);

		//make a list with miniatures representing miniatures of object and completing mark
		minis.push_back(std::make_unique<Graph>());
		minis.back()->loadFromFile(1.f, 1.f, "Assets/panel/" + treasures.back()->getAssetPath(), renderer);
		minis.back()->setXY(552 + 48 * (i - this->count), 584);
		minis.push_back(std::make_unique<Graph>());
		minis.back()->loadFromFile(1.f, 1.f, "Assets/panel/found.png", renderer);
		minis.back()->setXY(552 + 48 * (i - this->count) + 16, 600);

		//add compensation for harder tidbits
		if (tileW * tileH == 3) { motivationCompensation += 6; }
		else if (tileW == 4 || tileH == 4) { motivationCompensation += 4; }

		//making a pair of coords and treasure ID
		for (int r = 0; r < tileW; r++)
		{
			for (int c = 0; c < tileH; c++) { pairs.push_back(CoordsPair(x + 32 * r, y + 32 * c, i)); }
		}

		//adding to frame and treasure counter proper values
		framesLeft += tileW * tileH;
		treasuresLeft += 1;
	}

	//powerup management
	{
		int x, y, tileW = 2, tileH = 2;						//information about coords and tile dimensions
		bool isHere;										//flag with treasure validitation, true value force a next randomizing
		treasureType pType;									//contains information about treasure type

		//do until position is valid with another treasures (each other)
		do
		{
			//initalize values
			x = 0, y = 0;
			isHere = false;

			//randomize type and position of treasure
			pType = randomizePowerup();
			overand.randomCoordsTreasure(x, y, tileW, tileH);

			//prevention of setting treasures close to or one on another (making at least one tile width and height free space)
			//for each treasure already created (not this which is creating)
			for (int j = 0; j < treasures.size(); j++)
			{
				//if current position is too close previous position of treasure, change a randomizing flag to true
				if (((x + 32 * tileW + 32) > (treasures[j]->X() - 32)) && ((treasures[j]->X() + treasures[j]->W() + 32) > (x - 32))
					&& ((y + 32 * tileH + 32) > (treasures[j]->Y() - 32)) && ((treasures[j]->Y() + treasures[j]->H() + 32) > (y - 32))) {
					isHere = true;
				}
			}
		} while (isHere);

		//make a powerup and get path with randomize position
		powerup = Treasure(pType);
		powerup.loadFromFile(1.f, 1.f, "Assets/scene/" + powerup.getAssetPath(), renderer);
		powerup.setXY(x, y);

		//make a graphic representation of powerup readiness in panel/UI (star + icon)
		powerupIconUI = Treasure(pType);
		powerupIconUI.loadFromFile(1.f, 1.f, "Assets/panel/powerup_nused.png", renderer);
		powerupIconUI.setXY(352, 272);
		powerupStar = Graph(352, 272);
		powerupStar.loadFromFile(1.f, 1.f, "Assets/panel/powerups_nused.png", renderer);

		//making a pair of coords and append ID (for powerup is it ALWAYS 7)
		for (int r = 0; r < tileW; r++)
		{
			for (int c = 0; c < tileH; c++) { pairs.push_back(CoordsPair(x + 32 * r, y + 32 * c, 7)); }
		}

		powerupStatus = PowerupStatus::covered;										//change a status to ready for uncovered
	}
}

//render all treasures and miniatures objects
void TreasureManager::renderPanel(SDL_Renderer* renderer)
{
	powerupStar.render(renderer);													//showing powerup star on panel/UI
	powerupIconUI.render(renderer);													//showing powerup on panel/UI

	//for each miniatures on UI
	for (int i = 0; i < minis.size(); i++)
	{
		if (i % 2 == 0) { minis[i]->render(renderer); }								//showing miniatures of tidbits
		else if (!treasures[i/2]->getIsHidden()) { minis[i]->render(renderer); }	//showing a mark of finding a treasure
	}
}

//only render indicator for nosescan
void TreasureManager::renderScene(SDL_Renderer* renderer)
{
	//for each miniatures on scene
	for (int i = 0; i < treasures.size(); i++) { treasures[i]->render(renderer); }

	powerup.render(renderer);														//showing powerup on scene

}

//only render indicator for nosescan (needed to be above coverage)
void TreasureManager::renderIndicator(SDL_Renderer* renderer)
{
	//for nosescan - if is used and show to uncovered tile render an indicator
	if (showScanIndicator) { scanIndicator.render(renderer); }
}


//returns a value of treasures count (all, to find) and frames to find
int TreasureManager::getCount() { return count; }

int TreasureManager::getFramesLeft() { 	return framesLeft; }

int TreasureManager::getTreasuresLeft() { return treasuresLeft; }

//return score gathered during one frame
int TreasureManager::returnGatheredScore()
{
	int returnedScore = this->gatheredScore;
	this->gatheredScore = 0;
	return returnedScore;
}

int TreasureManager::getMotivationCompensation() { return this->motivationCompensation; }

PowerupStatus TreasureManager::getPowerupStatus() { return powerupStatus; }

treasureType TreasureManager::getPowerupType() { return powerup.getType(); }

//change power-up status to new one and change graphics in panel/UI properly
void TreasureManager::setPowerupStatus(PowerupStatus pupStat, SDL_Renderer* renderer)
{
	powerupStatus = pupStat;
	switch (powerupStatus)
	{
		case PowerupStatus::covered: default: 
		{ 
			powerupIconUI.loadFromFile(1.f, 1.f, "Assets/panel/powerup_nused.png", renderer);
			powerupStar.loadFromFile(1.f, 1.f, "Assets/panel/powerups_nused.png", renderer);
			break; 
		}
		case PowerupStatus::avaiable: 
		{ 
			powerupIconUI.loadFromFile(1.f, 1.f, "Assets/panel/" + powerup.getAssetPath(), renderer); 
			powerupStar.loadFromFile(1.f, 1.f, "Assets/panel/powerups_ready.png", renderer);
			break; 
		}
		case PowerupStatus::used: 
		{ 
			powerupIconUI.loadFromFile(1.f, 1.f, "Assets/panel/used" + powerup.getAssetPath(), renderer); 
			powerupStar.loadFromFile(1.f, 1.f, "Assets/panel/powerups_used.png", renderer);
			break; 
		}
	}
}

//nosescan ability method, chooses random number and enabling indicator
void TreasureManager::showRandomTile(SDL_Renderer* renderer)
{
	int index = overand.randomNumber(0, pairs.size() - 1);

	scanIndicator = Graph(pairs[index].x, pairs[index].y);
	scanIndicator.loadFromFile(1.f, 1.f, "Assets/scene/resultscan.png", renderer);
	showScanIndicator = true;

	setPowerupStatus(PowerupStatus::used, renderer);						//refresh power-up status
}

//checks a uncovered tile depending of character position
bool TreasureManager::checkTile(int x, int y)
{
	//for each pair of coords and ID
	for (int i = 0; i < pairs.size(); i++)
	{
		//if coords of pairs are equal with character coords
		if (pairs[i].x == x && pairs[i].y == y)
		{
			bool isLastTreasureTile = true;				//creates a flag of last tile of treasure, if is last tile the flag value is true
			int id = pairs[i].objectID;					//id of found treasure

			if (showScanIndicator && scanIndicator.X() == x && scanIndicator.Y() == y) { showScanIndicator = false; }

			pairs.erase(pairs.begin() + i);				//erase information of revealed tiles
			if (id != 7) { this->gatheredScore += 10; }	//add points of found part of treasure (not powerup)

			//for each rest of pairs
			for (int j = 0; j < pairs.size(); j++)
			{
				//if is another (at least one) tile with the same treasure as found, turn off finding last tile of treasure flag
				if (pairs[j].objectID == id) { j = pairs.size() - 1; isLastTreasureTile = false; }
			}
			if (id != 7) { framesLeft--; }				//decrement frame counter (not for power-up)
			//if the last tile of treasure was found, decrement treasure counter and add more score
			if (isLastTreasureTile)
			{
				//if fully found trasure is not a power-up, decrement treasure counter, show finding indicator and add score to gather
				if (id != 7) 
				{ 
					treasuresLeft--; 
					treasures[id]->setIsShown();
					this->gatheredScore += treasures[id]->getBaseScore();
				}
				//otherwise, add score to gather and change power-up status to "discovered" (ready to use)
				else
				{
					this->gatheredScore += powerup.getBaseScore();
					this->powerupStatus = PowerupStatus::discovered;
				}
			}
			return true;								//return true, if tile contained a treasure or powerup
		}
	}
	return false;										//return false, if tile did not contain a treasure or powerup
}

//clear or treasure object (Treasure, Pair, Miniatures vector) and reset all counters
void TreasureManager::exterminate()
{
	treasures.clear();
	pairs.clear();
	minis.clear();
	powerup.free();
	powerupIconUI.free();
	powerupStar.free();
	scanIndicator.free();
	count = 0;
	framesLeft = 0;
	treasuresLeft = 0;
	motivationCompensation = 0;
	powerupStatus = PowerupStatus::none;
	showScanIndicator = false;
}

//returns type of objects and writes information about tile dimensions
treasureType TreasureManager::randomizeType(int& tileW, int& tileH)
{
	switch (overand.randomNumber(1, 27))
	{
	case 1:		{ tileW = 2;	tileH = 2;	return treasureType::carrot;		break; }
	case 2:		{ tileW = 2;	tileH = 2;	return treasureType::mniszek;		break; }
	case 3:		{ tileW = 2;	tileH = 2;	return treasureType::salad;			break; }
	case 4:		{ tileW = 2;	tileH = 2;	return treasureType::banana;		break; }
	case 5:		{ tileW = 2;	tileH = 2;	return treasureType::strawBerry;	break; }
	case 6:		{ tileW = 1;	tileH = 3;	return treasureType::dill;			break; }
	case 7:		{ tileW = 2;	tileH = 2;	return treasureType::wildRose;		break; }
	case 8:		{ tileW = 4;	tileH = 1;	return treasureType::bamboo;		break; }
	case 9:		{ tileW = 1;	tileH = 4;	return treasureType::daisy;			break; }
	case 10:	{ tileW = 2;	tileH = 2;	return treasureType::eggplant;		break; }
	case 11:	{ tileW = 1;	tileH = 3;	return treasureType::alcea;			break; }
	case 12:	{ tileW = 3;	tileH = 1;	return treasureType::humulus;		break; }
	case 13:	{ tileW = 2;	tileH = 2;	return treasureType::quince;		break; }
	case 14:	{ tileW = 4;	tileH = 1;	return treasureType::asparagus;		break; }
	case 15:	{ tileW = 2;	tileH = 2;	return treasureType::kiwi;			break; }
	case 16:	{ tileW = 1;	tileH = 4;	return treasureType::parsnip;		break; }
	case 17:	{ tileW = 2;	tileH = 2;	return treasureType::cornflower;	break; }
	case 18:	{ tileW = 3;	tileH = 1;	return treasureType::timothy;		break; }
	case 19:
	{
		tileW = 3;	tileH = 2;
		if (overand.randomNumber(1, 200) == 200) { return treasureType::clover4; break; }
		else { return treasureType::clover3; break; }
	}
	case 20:	{ tileW = 2;	tileH = 2;	return treasureType::rutabaga;		break; }
	case 21:	{ tileW = 2;	tileH = 2;	return treasureType::cauliflower;	break; }
	case 22:	{ tileW = 2;	tileH = 2;	return treasureType::broccoli;		break; }
	case 23:	{ tileW = 4;	tileH = 1;	return treasureType::hibiscus;		break; }
	case 24:	{ tileW = 2;	tileH = 2;	return treasureType::apple;			break; }
	case 25:	{ tileW = 1;	tileH = 4;	return treasureType::kohlrabi;		break; }
	case 26:	{ tileW = 1;	tileH = 4;	return treasureType::forsythia;		break; }
	case 27:	{ tileW = 2;	tileH = 2;	return treasureType::rose;			break; }
	default:	{							return treasureType::none;			break; }
	}
}

treasureType TreasureManager::randomizePowerup()
{
	switch (overand.randomNumber(51, 53))
	{
	case 51: { return treasureType::dignine;		break; }
	case 52: { return treasureType::nosescan;		break; }
	case 53: { return treasureType::stubborntunism;	break; }
	default: { return treasureType::none;			break; }
	}
}
