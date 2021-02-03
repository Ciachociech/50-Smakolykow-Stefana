#include "Treasure.h"

Treasure::Treasure(treasureType type) : Graph(), type(type)/*, tileW(0), tileH(0)*/ {}

Treasure::Treasure(int x, int y, treasureType type) : Graph(x, y), type(type)/*, tileW(0), tileH(0)*/ {}

Treasure::~Treasure() {}

bool Treasure::loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	bool result;

	result = Graph::loadFromFile(scaleX, scaleY, filepath, renderer);
	if (result) 
	{
		//tileW = W() / 2;
		//tileH = H() / 2;
	}
	
	return result;
}

treasureType Treasure::getType() { return this->type; }

std::string Treasure::getAssetPath()
{
	switch (type)
	{
	case treasureType::carrot: { return std::string("marchewka.png"); break; }
	case treasureType::mniszek: { return std::string("mniszek.png"); break; }
	case treasureType::salad: { return std::string("salata.png"); break; }
	case treasureType::banana: { return std::string("banan.png"); break; }
	case treasureType::strawBerry: { return std::string("truskawka.png"); break; }
	case treasureType::dill: { return std::string("koperek.png"); break; }
	case treasureType::wildRose: { return std::string("dzikaroza.png"); break; }
	case treasureType::none: default: { return std::string(); break; }
	}
}

//int Treasure::getTileWidth() { return tileW; }

//int Treasure::getTileHeight() { return tileH; }

bool Treasure::getIsHidden() { return isHidden; }

void Treasure::setIsShown() { isHidden = false; }
