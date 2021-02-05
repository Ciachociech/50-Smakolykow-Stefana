#pragma once

#include "GraphLayer.h"
#include "OverworldRandomizer.h"

typedef std::vector<std::unique_ptr<GraphLayer>> VecGraphLayer;
enum class mood { none = -1, great, good, neutral, bad, horrible };

class LayerManager
{
public:
	LayerManager();
	virtual ~LayerManager();

	void addLayer(int mode, SDL_Renderer* renderer);
	void render(int x, int y, SDL_Renderer* renderer);
	void render(int mode, SDL_Renderer* renderer);
	void render(int x, int y, int mode, SDL_Renderer* renderer);
	bool disableTile(int x, int y);
	void refreshMood(int percent, SDL_Renderer* renderer);

	void exterminate();
private:
	VecGraphLayer layers;
	void modeInterpreter(int mode, SDL_Renderer* renderer);
	OverworldRandomizer overand;
	Graph bonus1, helpMe, bonus2, moodGraph;
	mood actualMood;
};