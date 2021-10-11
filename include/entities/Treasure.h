#pragma once
#include "Graph.h"

//enum containing information about treasure types
enum class treasureType { none = 0, carrot = 1, mniszek, salad, banana, strawBerry, dill, wildRose, bamboo, daisy, eggplant, alcea, humulus, quince, asparagus, kiwi, parsnip, cornflower, timothy, clover3, rutabaga, cauliflower, broccoli, hibiscus, apple, kohlrabi, forsythia, rose, silverweed, basil, pepper, dignine = 51, nosescan, stubborntunism, clover4 = 54 };

class Treasure : public Graph
{
public:
	Treasure(treasureType type);
	Treasure(int x, int y, treasureType type);
	~Treasure();

	bool loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer) override;

	treasureType getType();
	std::string getAssetPath();
	bool getIsHidden();
	int getBaseScore();

	void setIsShown();
private:
	treasureType type;										//treasure type
	bool isHidden = true;									//flag for showing treasure
	int baseScore = 0;										//score for revealing all tiles
};

