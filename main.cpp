//To not making mess in includes
#include "external_dependencies.h"

#include "LayerManager.h"
#include "StefanManager.h"
#include "SteeringManager.h"
#include "TreasureManager.h"
#include "TextManager.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Global SDL values
SDL_Window* window = NULL;
SDL_Surface* windowSurface = NULL;
SDL_Renderer* windowRenderer = NULL;
TTF_Font* font = NULL;

//Other constants
const int FPS = 60;
const std::string logoPath = "Assets/appLogo.png";

//Managers and game global params
LayerManager lm = LayerManager();
TreasureManager tm = TreasureManager();
StefanManager sm = StefanManager();
SteeringManager sterman = SteeringManager();
TextManager txtm = TextManager();
int level = 1;

bool init();
bool loadMedia();
void close();
bool loop();
void gameInit();

int main(int argc, char* args[])
{
	if (!init()) { printf("Failed to initialize!\n"); }
	else
	{
		if (!loadMedia()) { printf("Failed to load media!\n"); }
		else { loop(); }
	}
	close();
	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow(u8"50 Smako³yków Stefana (LUBie¿na Edycja)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (windowRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(windowRenderer, 32, 32, 32, 0xFF);

				windowSurface = SDL_GetWindowSurface(window);
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	//loading game logo
	SDL_Surface* surface = IMG_Load(logoPath.c_str());
	if (surface == NULL) { printf("Unable to load image %s! SDL Error: %s\n", logoPath.c_str(), SDL_GetError()); }
	else
	{
		SDL_SetWindowIcon(window, surface);
	}
	SDL_FreeSurface(surface);

	//loading font => source - https://www.dafont.com/wash-your-hand.font
	font = TTF_OpenFont("Assets/WashYourHand.ttf", 32);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	
	return success;
}

void close()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

bool loop()
{
	bool quit = false;
	SDL_Event event;

	gameInit();

	int tileX = 0, tileY = 0;
	Uint32 frameTime;
	keyAction actualAction;

	while (!quit)
	{
		tileX = 0, tileY = 0;
		frameTime = SDL_GetTicks();
		actualAction = keyAction::none;
		
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
				case SDL_QUIT: { quit = true; break; }
				case SDL_KEYDOWN: { actualAction = sterman.keyboardMovement(tileX, tileY, event.key.keysym.sym); break; }
				default: { break; }
			}
		}

		if (tm.getFramesLeft() == 0)
		{
			level++;
			gameInit();
			SDL_Delay(2000);
		}
		if (sm.getStefan().getMotivation() <= 0)
		{
			level = 1;
			gameInit();
			SDL_Delay(2000);
		}

		sm.moveStefan(tileX, tileY);
		if (actualAction == keyAction::digging) 
		{
			bool dug = lm.disableTile(sm.getStefan().X(), sm.getStefan().Y());
			if (dug) 
			{ 
				sm.reduceMotivation(); 
				txtm.update(std::to_string(sm.getStefan().getMotivation()), 4, font, windowRenderer);
			}
			if (tm.checkTile(sm.getStefan().X(), sm.getStefan().Y()))
			{
				txtm.update(std::to_string(tm.getFramesLeft()), 5, font, windowRenderer);
			}
		}

		SDL_RenderClear(windowRenderer);

		txtm.render(windowRenderer);
		lm.render(0, 0, 0, windowRenderer);
		tm.render(windowRenderer);
		lm.render(0, 0, 1, windowRenderer);
		sm.render(windowRenderer);

		if (actualAction == keyAction::mischievous || actualAction == keyAction::anotherEvil || actualAction == keyAction::steeringHelp) 
		{
			bool loop = true;
			SDL_Event event;
			while (loop)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					switch (event.type)
					{
					case SDL_QUIT: case SDL_KEYDOWN: { loop = false; break; }
					}
				}
				switch (actualAction)
				{
				case keyAction::mischievous: { lm.render(-1, windowRenderer); break; }
				case keyAction::anotherEvil: { lm.render(-2, windowRenderer); break; }
				case keyAction::steeringHelp: { lm.render(-3, windowRenderer); break; }
				default: { break; }
				}
				SDL_RenderPresent(windowRenderer);
			}

		}

		//SDL_UpdateWindowSurface(window);
		SDL_RenderPresent(windowRenderer);

		if((SDL_GetTicks() - frameTime) < (1000.f / FPS))
		SDL_Delay((1000.f / FPS) - (SDL_GetTicks() - frameTime));
	}

	return true;
}

void gameInit()
{
	lm.exterminate();
	lm.addLayer(0, windowRenderer);
	lm.addLayer(1, windowRenderer);
	
	tm.exterminate();
	tm.randomizeTreasures(windowRenderer);

	sm.exterminate();
	sm.setStefan(windowRenderer);
	sm.setMotivation(79 - (level > 10 ? 20 : 2 * level) + 4 * tm.getCount());

	txtm.exterminate();
	txtm.initalize(font, windowRenderer);
	txtm.update(std::to_string(level), 3, font, windowRenderer);
	txtm.update(std::to_string(sm.getStefan().getMotivation()), 4, font, windowRenderer);
	txtm.update(std::to_string(tm.getFramesLeft()), 5, font, windowRenderer);
}

