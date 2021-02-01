#include "LayerManager.h"

LayerManager::LayerManager() : layers(), overand(), bonus1(), bonus2(), helpMe() {}

LayerManager::~LayerManager() {}

void LayerManager::addLayer(int mode, SDL_Renderer* renderer)
{
	layers.push_back(std::make_unique<GraphLayer>());
	modeInterpreter(mode, renderer);
}

void LayerManager::render(int x, int y, SDL_Renderer* renderer)
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->render(x, y, renderer);
	}
}

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

void LayerManager::render(int x, int y, int mode, SDL_Renderer* renderer)
{
	switch (mode)
	{
	case -1: { bonus1.render(renderer); break; }
	case -2: { bonus2.render(renderer); break; }
	case -3: { helpMe.render(renderer); break; }
	default: { break; }
	}
	if (mode >= 0 && mode < layers.size())
	{
		layers[mode]->render(x, y, renderer);
	}
}

bool LayerManager::disableTile(int x, int y)
{
	return layers[1]->remove(x, y);
}

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

void LayerManager::modeInterpreter(int mode, SDL_Renderer* renderer)
{
	switch (mode)
	{
	case 0:
	{
		//ramka
		layers.back()->loadFromFile(0, 0, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(24, 0, 51.34f, 1.f, "Assets/frameH.png", renderer);
		layers.back()->loadFromFile(560, 0, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(1256, 0, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(0, 696, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(24, 696, 51.34f, 1.f, "Assets/frameH.png", renderer);
		layers.back()->loadFromFile(560, 696, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(1256, 696, 1.f, 1.f, "Assets/frameCone.png", renderer);
		layers.back()->loadFromFile(0, 24, 1.f, 28.f, "Assets/frameV.png", renderer);
		layers.back()->loadFromFile(560, 24, 1.f, 28.f, "Assets/frameV.png", renderer);
		layers.back()->loadFromFile(1256, 24, 1.f, 28.f, "Assets/frameV.png", renderer);

		layers.back()->loadFromFile(24, 48, 1.f, 1.f, "Assets/ingameLogo.png", renderer);

		//pole
		layers.back()->loadFromFile(584, 24, 1.f, 1.f, "Assets/boardEmpty.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 5, 24 + 32 * 5, 1.f, 1.f, "Assets/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 5, 24 + 32 * 13, 1.f, 1.f, "Assets/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 13, 24 + 32 * 5, 1.f, 1.f, "Assets/innerWall.png", renderer);
		layers.back()->loadFromFile(584 + 32 * 13, 24 + 32 * 13, 1.f, 1.f, "Assets/innerWall.png", renderer);
		modeInterpreter(-1, renderer);
		break;
	}
	case -1: 
	{ 
		bonus1 = Graph(0, 0); 
		bonus1.loadFromFile(1.f, 1.f, "Assets/haveANiceDay.png", renderer); 
		bonus2 = Graph(0, 0); 
		bonus2.loadFromFile(1.f, 1.f, "Assets/haveANiceDay.png", renderer);
		helpMe = Graph(0, 0); 
		helpMe.loadFromFile(1.f, 1.f, "Assets/helpMe.png", renderer);

		break; 
	}
	case 1:
	{
		for (int r = 0; r < 21; r++)
		{
			for (int c = 0; c < 21; c++)
			{
				if (((r >= 5 && r <= 7) && (c >= 5 && c <= 7)) || ((r >= 13 && r <= 15) && (c >= 5 && c <= 7)) || ((r >= 5 && r <= 7) && (c >= 13 && c <= 15)) || ((r >= 13 && r <= 15) && (c >= 13 && c <= 15))) {}
				else { layers.back()->loadFromFile(584 + 32 * c, 24 + 32 * r, 1.f, 1.f, "Assets/pellet.png", renderer); }
			}
		}
		break;
	}
	default: { break; }
	}
}
