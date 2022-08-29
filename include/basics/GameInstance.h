#pragma once

#include "..\..\include\basics\GameScene.h"
#include "..\..\include\menu\GameMenu.h"

enum class sceneState { splashscreen = 0, mainmenu, game, highscores, options, pausemenu, gameover, entermenu };
enum class keyState { defeat = -3, ragequit = -2, pause = -1, none };

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
	const std::string gameVersion = "0.11";
	const std::string windowNamePL = u8"50 Smako³yków Stefana (£aciata edycja " + gameVersion + ")";
	const std::string windowNameEN = u8"50 Tidbits of Stefan (Piebald Edition " + gameVersion + ")";
	
	//Game managers
	LayerManager lm = LayerManager();
	TreasureManager tm = TreasureManager();
	StefanManager sm = StefanManager();
	SteeringManager sterman = SteeringManager();
	TextManager txtm = TextManager(gameVersion);
	DatInterpreter dati = DatInterpreter("src/ftos.dat", gameVersion);		//it has to be "ftos.dat" to proper execution
	AudioManager am = AudioManager();
	OptionsManager om = OptionsManager();
	ScoreManager scorman = ScoreManager();

	//App functions
	bool init();
	bool loadMedia();
	void close();
	bool loop();
	void render();
	void updateSceneState(sceneState newState);
	void appendOptions();
	void initMenu(GameMenu& menu, textType tt);
	bool showScore(bool success);

	//Status of game
	sceneState actualScene, lastScene;
	keyState actualKeyState;
	GameScene game = GameScene();
	GameMenu mainMenu = GameMenu(4), pauseMenu = GameMenu(3), optionsMenu = GameMenu(2), hiscoresMenu = GameMenu(0), gameOverMenu = GameMenu(2), enterNameMenu = GameMenu(-1);
public:
	GameInstance();
	virtual ~GameInstance();

	void run();
};

