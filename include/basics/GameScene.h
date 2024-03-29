#pragma once

#include "..\..\include\managers\LayerManager.h"
#include "..\..\include\managers\StefanManager.h"
#include "..\..\include\managers\SteeringManager.h"
#include "..\..\include\managers\TreasureManager.h"
#include "..\..\include\managers\TextManager.h"
#include "..\..\include\basics\DatInterpreter.h"
#include "..\..\include\managers\AudioManager.h"
#include "..\..\include\managers\ScoreManager.h"

class GameScene
{
private:
	//Global SDL values
	SDL_Renderer *windowRenderer = NULL;
	TTF_Font *font = NULL;

	//Game managers
	LayerManager lm = LayerManager();
	TreasureManager tm = TreasureManager();
	StefanManager sm = StefanManager();
	SteeringManager *sterman = NULL;
	TextManager *txtm = NULL;
	DatInterpreter *dati = NULL;
	AudioManager *am = NULL;
	ScoreManager* scorman = NULL;

	//Other global values
	int level = 1, winRewardStage = 0, foundSnacks = 0;
	bool isLost = false;

	keyAction actualAction;									//shows information about last chosen action (by keyboard)
public:
	GameScene();
	virtual ~GameScene();

	//loading pointers to instance managers and objects
	void loadRenderer(SDL_Renderer* rend);
	void loadFont(TTF_Font* font);
	void loadSteering(SteeringManager* sm);
	void loadTexting(TextManager* tm);
	void loadDating(DatInterpreter* dati);
	void loadAudio(AudioManager* am);
	void loadScores(ScoreManager* sm);

	//Game functions
	int loop();
	void init();
	void reset();
	void close();
	void render();
	void renderScene();
	void renderPanel();

	int getLevel();
	int getFoundSnacks();

	//Game mechanics functions
	void digTile(bool isDignine = false);
};

