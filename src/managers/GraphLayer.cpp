#include "..\..\include\managers\GraphLayer.h"

GraphLayer::GraphLayer() : elements() {}

GraphLayer::~GraphLayer() {}

//load a texture at the certain position, scale and file
bool GraphLayer::loadFromFile(int x, int y, float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	//flag for showing a success of initalization, can be set to false when something goes wrong
	bool success;

	elements.push_back(std::make_unique<Graph>());									//append new Graph object to vector
	success = elements.back()->loadFromFile(scaleX, scaleY, filepath, renderer);	//loads an image and returns a result of this operation
	elements.back()->setXY(x, y);													//sets coords of image

	return success;
}

//render each object in layer
void GraphLayer::render(int x, int y, SDL_Renderer* renderer)
{
	for (int i = 0; i < elements.size(); i++) { elements[i]->render(x, y, renderer); }
}

//remove object which share coords given as arguments
bool GraphLayer::remove(int x, int y)
{
	for (int i = 0; i < elements.size(); i++)
	{
		//if coords are compatible, erase this element and return true
		if (elements[i]->X() == x && elements[i]->Y() == y) { elements.erase(elements.begin() + i); return true; }
	}
	return false;																	//returns false, when none element was removed
}

//delete all objects
void GraphLayer::exterminate() { elements.clear(); }
