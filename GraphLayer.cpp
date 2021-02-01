#include "GraphLayer.h"

GraphLayer::GraphLayer() : elements() {}

GraphLayer::~GraphLayer() {}

bool GraphLayer::loadFromFile(int x, int y, float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	bool success;

	elements.push_back(std::make_unique<Graph>());
	success = elements.back()->loadFromFile(scaleX, scaleY, filepath, renderer);
	elements.back()->setXY(x, y);

	return success;
}

void GraphLayer::render(int x, int y, SDL_Renderer* renderer)
{
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->render(x, y, renderer);
	}
}

void GraphLayer::render(int x, int y, int height, bool isAbove, SDL_Renderer* renderer)
{
	for (int i = 0; i < elements.size(); i++)
	{
		bool performRender = false;
		if (isAbove)
		{
			if (elements[i]->Y() < height) { performRender = true; }
		}
		else
		{
			if (elements[i]->Y() > height) { performRender = true; }
		}
		if (performRender) { elements[i]->render(x, y, renderer); }
	}
}

bool GraphLayer::remove(int x, int y)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->X() == x && elements[i]->Y() == y) { elements.erase(elements.begin() + i); return true; }
	}
	return false;
}

void GraphLayer::exterminate() { elements.clear(); }
