#include "TreasureManager.h"

TreasureManager::TreasureManager() : overand(), treasures(), count(0), framesLeft(0), treasuresLeft(0), gatheredScore(0), pairs() {}

TreasureManager::~TreasureManager() { treasures.~vector(); pairs.~vector(); }

void TreasureManager::randomizeTreasures(SDL_Renderer* renderer)
{
	this->count = overand.randomNumber(4, 5);

	for (int i = 0; i < this->count; i++) 
	{
		int x, y, tileW, tileH;
		bool isHere;
		treasureType tType;

		do
		{
			x = 0, y = 0, tileW = 0, tileH = 0;
			isHere = false;

			tType = randomizeType(tileW, tileH);
			overand.randomCoordsTreasure(x, y, tileW, tileH);

			for (int j = 0; j < treasures.size(); j++) //zapobiega losowaniu smako³yków obok siebie lub na sobie (np. 2 smako³yki dziel¹ce wspóln¹ kratkê)
			{
				if (((x + 32 * tileW + 32) > (treasures[j]->X() - 32)) && ((treasures[j]->X() + treasures[j]->W() + 32) > (x - 32)) 
					&& ((y + 32 * tileH + 32) > (treasures[j]->Y() - 32)) && ((treasures[j]->Y() + treasures[j]->H() + 32) > (y - 32))) { isHere = true; }
			}

		} while (isHere);
		
		treasures.push_back(std::make_unique<Treasure>(tType));
		treasures.back()->loadFromFile(1.f, 1.f, "Assets/scene/" + treasures.back()->getAssetPath(), renderer);
		treasures.back()->setXY(x, y);

		minis.push_back(std::make_unique<Graph>());
		minis.back()->loadFromFile(1.f, 1.f, "Assets/panel/" + treasures.back()->getAssetPath(), renderer);
		minis.back()->setXY(552 + 48 * (i - this->count), 584);
		minis.push_back(std::make_unique<Graph>());
		minis.back()->loadFromFile(1.f, 1.f, "Assets/panel/found.png", renderer);
		minis.back()->setXY(552 + 48 * (i - this->count) + 16, 600);

		for (int r = 0; r < tileW; r++)
		{
			for (int c = 0; c < tileH; c++) { pairs.push_back(CoordsPair(x + 32 * r, y + 32 * c, i)); }
		}

		framesLeft += tileW * tileH;
		treasuresLeft += 1;
	}
}

void TreasureManager::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < treasures.size(); i++)
	{
		treasures[i]->render(renderer);
	}
	for (int i = 0; i < minis.size(); i++)
	{
		if (i % 2 == 0) { minis[i]->render(renderer); }	//pokazywanie miniatur smako³yku
		else if (!treasures[i/2]->getIsHidden()) { minis[i]->render(renderer); }	//pokazywanie znacznika znalezienia smako³yku
	}
}

int TreasureManager::getCount() { return count; }

int TreasureManager::getFramesLeft()
{
	if (framesLeft == pairs.size()) { return framesLeft; }
	else { return -1; }
}

int TreasureManager::getTreasuresLeft() { return treasuresLeft; }

int TreasureManager::returnGatheredScore()
{
	int returnedScore = this->gatheredScore;
	this->gatheredScore = 0;
	return returnedScore;
}

bool TreasureManager::checkTile(int x, int y)
{
	if (pairs.size() == framesLeft)		//kontrolne sprawdzenie, czy wartoœci siê zgadzaj¹
	{
		for (int i = 0; i < pairs.size(); i++)	//jezeli wspó³rzêdne jednej z kratek smako³yku zgadza siê ze wspó³rzêdnymi Stefana (po wykopaniu)
		{
			if (pairs[i].x == x && pairs[i].y == y) 
			{ 
				bool isLastTreasureTile = true;
				int id = pairs[i].objectID;

				pairs.erase(pairs.begin() + i); // usuwanie informacji o odkrytej kratce
				this->gatheredScore += 10;
				for (int j = 0; j < pairs.size(); j++)	//je¿eli jeszcze jest jakakolwiek kratka chowaj¹ca smako³yk
				{
					if (pairs[j].objectID == id) { j = pairs.size() - 1; isLastTreasureTile = false; }
				}
				framesLeft--; 
				if (isLastTreasureTile)	//je¿eli nie ma kratek chowaj¹cych konkretny smako³yk
				{
					treasuresLeft--;
					treasures[id]->setIsShown();
					this->gatheredScore += treasures[id]->getBaseScore();
				}
				return true; 
			}
		}
		return false;
	}
	else { return false; }
}

void TreasureManager::exterminate()
{
	treasures.clear();
	pairs.clear();
	minis.clear();
	count = 0;
	framesLeft = 0;
	treasuresLeft = 0;
}

treasureType TreasureManager::randomizeType(int& tileW, int& tileH)
{
	switch (overand.randomNumber(1, 10))
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
	default:{								return treasureType::none;			break; }
	}
}
