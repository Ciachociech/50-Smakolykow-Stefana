#include "Treasure.h"

Treasure::Treasure(treasureType type) : Graph(), type(type) {}

Treasure::Treasure(int x, int y, treasureType type) : Graph(x, y), type(type) {}

Treasure::~Treasure() {}

bool Treasure::loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	bool result;

	result = Graph::loadFromFile(scaleX, scaleY, filepath, renderer);
	if (result) {}
	
	return result;
}

treasureType Treasure::getType() { return this->type; }

std::string Treasure::getAssetPath()
{
	switch (type)
	{
	case treasureType::carrot:		{ baseScore = 40; return std::string("marchewka.png"); break; }
	case treasureType::mniszek:		{ baseScore = 40; return std::string("mniszek.png"); break; }
	case treasureType::salad:		{ baseScore = 40; return std::string("salata.png"); break; }
	case treasureType::banana:		{ baseScore = 40; return std::string("banan.png"); break; }
	case treasureType::strawBerry:	{ baseScore = 40; return std::string("truskawka.png"); break; }
	case treasureType::dill:		{ baseScore = 60; return std::string("koperek.png"); break; }
	case treasureType::wildRose:	{ baseScore = 40; return std::string("dzikaroza.png"); break; }
	case treasureType::bamboo:		{ baseScore = 60; return std::string("bamboo.png"); break; }
	case treasureType::none: default: { return std::string(); break; }
	}
}

//int Treasure::getTileWidth() { return tileW; }

//int Treasure::getTileHeight() { return tileH; }

bool Treasure::getIsHidden() { return isHidden; }

int Treasure::getBaseScore() { return this->baseScore; }

void Treasure::setIsShown() { isHidden = false; }
