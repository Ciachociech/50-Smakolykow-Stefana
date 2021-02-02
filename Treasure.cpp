#include "Treasure.h"

Treasure::Treasure(treasureType type) : Graph(), type(type), tileW(0), tileH(0) {}

Treasure::Treasure(int x, int y, treasureType type) : Graph(x, y), type(type), tileW(2), tileH(2) {}

Treasure::~Treasure() {}

treasureType Treasure::getType() { return this->type; }

std::string Treasure::getAssetPath()
{
	switch (type)
	{
	case treasureType::carrots: { return std::string("marchewka.png"); break; }
	case treasureType::mniszek: { return std::string("mniszek.png"); break; }
	case treasureType::salad: { return std::string("salata.png"); break; }
	case treasureType::banana: { return std::string("banan.png"); break; }
	case treasureType::none: default: { return std::string(); break; }
	}
}
