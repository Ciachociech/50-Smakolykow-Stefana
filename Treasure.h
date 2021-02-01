#pragma once
#include "Graph.h"

enum class treasureType { none = 0, carrots = 1, mniszek, salad };

class Treasure : public Graph
{
public:
	Treasure(treasureType type);
	Treasure(int x, int y, treasureType type);
	~Treasure();

	treasureType getType();
	std::string getAssetPath();
private:
	treasureType type;
	int tileW, tileH;
};

