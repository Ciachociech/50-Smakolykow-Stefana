#include "Treasure.h"

Treasure::Treasure(treasureType type) : Graph(), type(type), tileW(0), tileH(0) {}

Treasure::Treasure(int x, int y, treasureType type) : Graph(x, y), type(type), tileW(2), tileH(2) {}

Treasure::~Treasure() {}

treasureType Treasure::getType() { return this->type; }

std::string Treasure::getAssetPath()
{
	switch (type)
	{
	case treasureType::carrots: { return std::string("Assets/marchewki.png"); break; }
	case treasureType::mniszek: { return std::string("Assets/mniszek.png"); break; }
	case treasureType::salad: { return std::string("Assets/salata.png"); break; }
	case treasureType::none: default: { return std::string(); break; }
	}
}
