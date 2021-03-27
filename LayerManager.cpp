#include "LayerManager.h"

LayerManager::LayerManager() : layers(), overand(), bonus1(), bonus2(), helpMe(), moodGraph(), actualMood(mood::none) {}

LayerManager::~LayerManager() {}

//add layer and fill it with proper objects
void LayerManager::addLayer(int mode, SDL_Renderer* renderer)
{
	layers.push_back(std::make_unique<GraphLayer>());							//append new GraphLayer object to vector
	modeInterpreter(mode, renderer);											//fill new GraphLayer object
}

//render all objects in each layer
void LayerManager::render(int x, int y, SDL_Renderer* renderer)
{
	for (int i = 0; i < layers.size(); i++) { layers[i]->render(x, y, renderer); }
}

//render selected special object
void LayerManager::render(int mode, SDL_Renderer* renderer)
{
	switch (mode)
	{
	case -1: { bonus1.render(renderer); break; }
	case -2: { bonus2.render(renderer); break; }
	case -3: { helpMe.render(renderer); break; }
	default: { break; }
	}
}

//render selected special object or certain layer including camera position
void LayerManager::render(int x, int y, int mode, SDL_Renderer* renderer)
{
	switch (mode)
	{
	case -1: { bonus1.render(renderer); break; }
	case -2: { bonus2.render(renderer); break; }
	case -3: { helpMe.render(renderer); break; }
	case 0: { moodGraph.render(renderer); break; }
	default: { break; }
	}
	if (mode >= 0 && mode < layers.size()) { layers[mode]->render(x, y, renderer); }
}

//removes tile with certain coords
bool LayerManager::disableTile(int x, int y) { return layers[1]->remove(x, y); }

//changes texture for mood depending of motivation percentage (actual / max)
void LayerManager::refreshMood(int percent, SDL_Renderer* renderer)
{
	if (percent >= 81 && actualMood != mood::great) 
	{
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_great.png", renderer); actualMood = mood::great;
	}
	else if (percent >= 61 && percent < 81 && actualMood != mood::good) 
	{ 
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_good.png", renderer); actualMood = mood::good;
	}
	else if (percent >= 41 && percent < 61 && actualMood != mood::neutral) 
	{ 
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_neutral.png", renderer); actualMood = mood::neutral;
	}
	else if (percent >= 21 && percent < 41 && actualMood != mood::bad) 
	{ 
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_bad.png", renderer); actualMood = mood::bad;
	}
	else if (percent < 21 && actualMood != mood::horrible) 
	{
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_horrible.png", renderer); actualMood = mood::horrible;
	}
}

//delete all graphic object (special and each layer)
void LayerManager::exterminate()
{
	bonus1.free();
	bonus2.free();
	helpMe.free();
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->exterminate();
	}
	layers.clear();
}

//fills layers or objects depending of chosen mode
void LayerManager::modeInterpreter(int mode, SDL_Renderer* renderer)
{
	switch (mode)
	{
	case 0:
	{
		//frame
		layers.back()->loadFromFile(0, 0, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(24, 0, 51.34f, 1.f, "Assets/panel/frameH.png", renderer);
		layers.back()->loadFromFile(560, 0, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(1256, 0, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(0, 696, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(24, 696, 51.34f, 1.f, "Assets/panel/frameH.png", renderer);
		layers.back()->loadFromFile(560, 696, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(1256, 696, 1.f, 1.f, "Assets/panel/frameCone.png", renderer);
		layers.back()->loadFromFile(0, 24, 1.f, 28.f, "Assets/panel/frameV.png", renderer);
		layers.back()->loadFromFile(560, 24, 1.f, 28.f, "Assets/panel/frameV.png", renderer);
		layers.back()->loadFromFile(1256, 24, 1.f, 28.f, "Assets/panel/frameV.png", renderer);

		//logo
		layers.back()->loadFromFile(24, 24, 1.f, 1.f, "Assets/panel/ingameLogo.png", renderer);

		//mood
		moodGraph = Graph(116, 272);
		moodGraph.loadFromFile(1.f, 1.f, "Assets/panel/mood_neutral.png", renderer);

		//field
		layers.back()->loadFromFile(584, 24, 1.f, 1.f, "Assets/scene/boardEmpty.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 5, 24 + 32 * 5, 1.f, 1.f, "Assets/scene/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 5, 24 + 32 * 13, 1.f, 1.f, "Assets/scene/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 13, 24 + 32 * 5, 1.f, 1.f, "Assets/scene/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 13, 24 + 32 * 13, 1.f, 1.f, "Assets/scene/innerWall.png", renderer);
		modeInterpreter(-1, renderer);
		break;
	}
	//special objects
	case -1: 
	{ 
		bonus1 = Graph(0, 0); 
		bonus1.loadFromFile(1.f, 1.f, "Assets/other/haveANiceDay.png", renderer); 
		bonus2 = Graph(0, 0); 
		bonus2.loadFromFile(1.f, 1.f, "Assets/other/haveANiceDay.png", renderer);
		helpMe = Graph(0, 0); 
		helpMe.loadFromFile(1.f, 1.f, "Assets/other/helpMe.png", renderer);

		break; 
	}
	//covering
	case 1:
	{
		for (int r = 0; r < 21; r++)
		{
			for (int c = 0; c < 21; c++)
			{
				if (((r >= 5 && r <= 7) && (c >= 5 && c <= 7)) || ((r >= 13 && r <= 15) && (c >= 5 && c <= 7)) || ((r >= 5 && r <= 7) && (c >= 13 && c <= 15)) || ((r >= 13 && r <= 15) && (c >= 13 && c <= 15))) {}
				else { layers.back()->loadFromFile(584 + 32 * c, 24 + 32 * r, 1.f, 1.f, "Assets/scene/pellet.png", renderer); }
			}
		}
		break;
	}
	default: { break; }
	}
}
