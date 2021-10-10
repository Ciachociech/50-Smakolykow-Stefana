#pragma once

#include "..\..\include\managers\SteeringManager.h"
#include "..\..\include\managers\TextManager.h"

class GameMenu
{
private:
	//Global SDL values
	SDL_Renderer* windowRenderer = NULL;
	TTF_Font* font = NULL;

	//Game managers
	SteeringManager* sterman = NULL;
	TextManager* txtm = NULL;

	OverworldRandomizer overand;
	keyAction actualAction;									//shows information about last chosen action (by keyboard)
	int actualOption = 0, maxOptions;
	bool isEntering;
	std::string editableString;

	//menu/enter loops
	int menuLoop();
	int enterLoop();
public:
	GameMenu();
	GameMenu(int optionsCount);
	virtual ~GameMenu();
	
	//loading pointers to instance managers and objects
	void loadRenderer(SDL_Renderer* rend);
	void loadFont(TTF_Font* font);
	void loadSteering(SteeringManager* sm);
	void loadTexting(TextManager* tm);

	//Game functions
	int loop();
	void init(textType tt);
	void close();
	void render(textType tt);

	int getActualOption();
	int getMaxOptions();
	std::string getEditableString();

	void setEditableString(std::string setEditableString);

	Graph logo, cursor;
};

