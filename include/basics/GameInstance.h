#pragma once

#include "..\..\include\managers\LayerManager.h"
#include "..\..\include\managers\StefanManager.h"
#include "..\..\include\managers\SteeringManager.h"
#include "..\..\include\managers\TreasureManager.h"
#include "..\..\include\managers\TextManager.h"
#include "..\..\include\basics\DatInterpreter.h"
#include "..\..\include\managers\AudioManager.h"

#include "..\..\include\basics\Score.h"

class GameInstance
{
private:
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
	const std::string logoPath = "Assets/other/appLogo.png";
	const std::string gameVersion = "0.9.2";
	const std::string windowName = u8"50 Smako³yków Stefana (£aciata edycja " + gameVersion + u8")";
	
	//Game managers
	LayerManager lm = LayerManager();
	TreasureManager tm = TreasureManager();
	StefanManager sm = StefanManager();
	SteeringManager sterman = SteeringManager();
	TextManager txtm = TextManager();
	DatInterpreter dati = DatInterpreter("src/ftos.dat", gameVersion);		//it has to be "ftos.dat" to proper execution
	AudioManager am = AudioManager();

	//Other global values
	int level = 1, winRewardStage = 0, foundSnacks = 0;
	bool isLost = false;
	Score score = Score(), bestScore = Score(-1);

	//App functions
	bool init();
	bool loadMedia();
	void close();
	bool loop();
	void gameInit();

	//Game mechanics functions
	void digTile(bool isDignine = false);
public:
	GameInstance();
	virtual ~GameInstance();

	void run();
};

