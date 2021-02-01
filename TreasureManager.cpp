#include "TreasureManager.h"

TreasureManager::TreasureManager() : overand(), treasures(), count(0), framesLeft(0), pairs() {}

TreasureManager::~TreasureManager() { treasures.~vector(); pairs.~vector(); }

void TreasureManager::randomizeTreasures(SDL_Renderer* renderer)
{
	this->count = overand.randomNumber(4, 5);

	for (int i = this->count; i != 0; i--) {
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
		treasures.back()->loadFromFile(1.f, 1.f, treasures.back()->getAssetPath(), renderer);
		treasures.back()->setXY(x, y);
		pairs.push_back(CoordsPair(x, y));
		pairs.push_back(CoordsPair(x+32, y));
		pairs.push_back(CoordsPair(x, y+32));
		pairs.push_back(CoordsPair(x+32, y+32));

		framesLeft += 4;
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

bool TreasureManager::checkTile(int x, int y)
{
	if (pairs.size() == framesLeft)
	{
		for (int i = 0; i < pairs.size(); i++)
		{
			if (pairs[i].x == x && pairs[i].y == y) { pairs.erase(pairs.begin() + i); framesLeft--; return true; }
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
}

treasureType TreasureManager::randomizeType()
{
	switch (overand.randomNumber(1, 3))
	{
	case 1: { return treasureType::carrots; break; }
	case 2: { return treasureType::mniszek; break; }
	case 3: { return treasureType::salad; break; }
	default: { return treasureType::none; break; }
	}
}
