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
		do
		{
			x = 0, y = 0;
			isHere = false;

			overand.randomCoordsTreasure(x, y);

			for (int j = 0; j < treasures.size(); j++)
			{
				if (((x + 96) > (treasures[j]->X() - 32)) && ((treasures[j]->X() + 96) > (x - 32)) && ((y + 96) > (treasures[j]->Y() - 32)) && ((treasures[j]->Y() + 96) > (y - 32))) { isHere = true; }
			}

		} while (isHere);
		
		treasures.push_back(std::make_unique<Treasure>(randomizeType()));
		treasures.back()->loadFromFile(1.f, 1.f, "Assets/scene/"+treasures.back()->getAssetPath(), renderer);
		treasures.back()->setXY(x, y);
		pairs.push_back(CoordsPair(x, y, i));
		pairs.push_back(CoordsPair(x+32, y, i));
		pairs.push_back(CoordsPair(x, y+32, i));
		pairs.push_back(CoordsPair(x+32, y+32, i));

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
	if (pairs.size() == framesLeft)
	{
		for (int i = 0; i < pairs.size(); i++)
		{
			if (pairs[i].x == x && pairs[i].y == y) 
			{ 
				bool isLastTreasureTile = true;
				int id = pairs[i].objectID;

				pairs.erase(pairs.begin() + i);
				for (int j = 0; j < pairs.size(); j++)
				{
					if (pairs[j].objectID == id) { j = pairs.size() - 1; isLastTreasureTile = false; }
				}
				framesLeft--; 
				if (isLastTreasureTile) { treasuresLeft--; }
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
	count = 0;
	framesLeft = 0;
	treasuresLeft = 0;
}

treasureType TreasureManager::randomizeType()
{
	switch (overand.randomNumber(1, 4))
	{
	case 1: { return treasureType::carrots; break; }
	case 2: { return treasureType::mniszek; break; }
	case 3: { return treasureType::salad; break; }
	case 4: { return treasureType::banana; break; }
	default: { return treasureType::none; break; }
	}
}
