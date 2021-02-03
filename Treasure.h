#pragma once
#include "Graph.h"

enum class treasureType { none = 0, carrot = 1, mniszek, salad, banana, strawBerry, dill, wildRose };

class Treasure : public Graph
{
public:
	Treasure(treasureType type);
	Treasure(int x, int y, treasureType type);
	~Treasure();

	bool loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer) override;

	treasureType getType();
	std::string getAssetPath();
	//int getTileWidth();
	//int getTileHeight();
	bool getIsHidden();

	void setIsShown();
private:
	treasureType type;
	//int tileW, tileH;
	bool isHidden = true;
};
