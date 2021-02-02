#pragma once

#include "Graph.h"

class GraphLayer
{
public:
	GraphLayer();
	~GraphLayer();

	bool loadFromFile(int x, int y, float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer);
	virtual void render(int x, int y, SDL_Renderer* renderer);
	virtual void render(int x, int y, int height, bool isAbove, SDL_Renderer* renderer);

	bool remove(int x, int y);
	void exterminate();
private:
	VecGraph elements;
};

