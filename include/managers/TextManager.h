#pragma once

#include "..\external_dependencies.h"

#include "..\entities\Text.h"
#include "..\basics\OverworldRandomizer.h"

enum class textType { none = 0, scene = 1, menu, scores, options, pause, gameover, enterName };

typedef std::vector<std::unique_ptr<Text>> VecText;

class TextManager
{
public:
	TextManager();
	TextManager(std::string version);
	virtual ~TextManager();

	//more general functions of initalizing and updating
	void initalize(textType tt, TTF_Font* font, SDL_Renderer* renderer);
	void update(textType tt, std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);

	void render(textType tt, SDL_Renderer* renderer);
	void exterminate();
	void exterminate(textType tt);

	textType actualTextType;
private:
	std::string version;

	//vectors of Text objects
	VecText sceneTexts, menuTexts, scoresTexts, optTexts, pauseTexts, gameoverTexts, enterNameTexts;

	OverworldRandomizer overand;		//randomizer

	//initalize (and prepare to render) text depending on text type
	void initalizeTextScene(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextMenu(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextPause(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextOptions(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextHiscores(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextGameOver(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextEnterName(TTF_Font* font, SDL_Renderer* renderer);

	//update string (and prepare to render) for some type of text
	void updateTextScene(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);
	void updateTextMenu(TTF_Font* font, SDL_Renderer* renderer, bool isGraying = true);
	void updateTextOptions(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);
	void updateTextHiscores(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);
	void updateTextEnterName(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);

	//make text more or less visible/bright
	SDL_Color greyColor(SDL_Color oldColor);
	SDL_Color ungreyColor(SDL_Color oldColor);
};

