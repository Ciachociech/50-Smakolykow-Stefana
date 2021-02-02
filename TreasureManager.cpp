#include "TreasureManager.h"

TreasureManager::TreasureManager() : overand(), treasures(), count(0), framesLeft(0), treasuresLeft(0), pairs() {}

TreasureManager::~TreasureManager() { treasures.~vector(); pairs.~vector(); }

void TreasureManager::randomizeTreasures(SDL_Renderer* renderer)
{
	this->count = overand.randomNumber(4, 5);

	for (int i = 0; i < this->count; i++) 
	{
		int x, y;
		bool isHere;
		treasureType tType;

		do
		{
			x = 0, y = 0;
			isHere = false;

			tType = randomizeType();
			overand.randomCoordsTreasure(x, y);

			for (int j = 0; j < treasures.size(); j++)
			{
				if (((x + 96) > (treasures[j]->X() - 32)) && ((treasures[j]->X() + 96) > (x - 32)) && ((y + 96) > (treasures[j]->Y() - 32)) && ((treasures[j]->Y() + 96) > (y - 32))) { isHere = true; }
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

		pairs.push_back(CoordsPair(x, y, i));
		pairs.push_back(CoordsPair(x + 32, y, i));
		pairs.push_back(CoordsPair(x, y + 32, i));
		pairs.push_back(CoordsPair(x + 32, y + 32, i));

		framesLeft += 4;
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
				for (int j = 0; j < pairs.size(); j++)	//je¿eli jeszcze jest jakakolwiek kratka chowaj¹ca smako³yk
				{
					if (pairs[j].objectID == id) { j = pairs.size() - 1; isLastTreasureTile = false; }
				}
				framesLeft--; 
				if (isLastTreasureTile)	//je¿eli nie ma kratek chowaj¹ca konkretny smako³yk
				{
					treasuresLeft--; treasures[id]->setIsShown();
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

treasureType TreasureManager::randomizeType()
{
	switch (overand.randomNumber(1, 5))
	{
	case 1: { return treasureType::carrot; break; }
	case 2: { return treasureType::mniszek; break; }
	case 3: { return treasureType::salad; break; }
	case 4: { return treasureType::banana; break; }
	case 5: { return treasureType::strawBerry; break; }
	default: { return treasureType::none; break; }
	}
}
