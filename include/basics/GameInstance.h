#pragma once

#include "..\..\include\basics\GameScene.h"
#include "..\..\include\basics\GameMenu.h"

enum class sceneState { splashscreen = 0, mainmenu, game, highscores, options, pausemenu };
enum class keyState { ragequit = -2, pause = -1, none };

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
	const std::string gameVersion = "0.9.3";
	const std::string windowName = u8"50 Smako³yków Stefana (£aciata edycja " + gameVersion + ")";
	
	//Game managers
	LayerManager lm = LayerManager();
	TreasureManager tm = TreasureManager();
	StefanManager sm = StefanManager();
	SteeringManager sterman = SteeringManager();
	TextManager txtm = TextManager();
	DatInterpreter dati = DatInterpreter("src/ftos.dat", gameVersion);		//it has to be "ftos.dat" to proper execution
	AudioManager am = AudioManager();

	//App functions
	bool init();
	bool loadMedia();
	void close();
	bool loop();
	void render();

	//Status of game
	sceneState actualScene;
	keyState actualKeyState;
	GameScene game = GameScene();
	GameMenu mainMenu = GameMenu(4), pauseMenu = GameMenu(3);
public:
	GameInstance();
	virtual ~GameInstance();

	void run();
};

