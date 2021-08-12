#pragma once

#include "..\external_dependencies.h"

#include "..\entities\Text.h"
#include "..\basics\OverworldRandomizer.h"

enum class textType { none = 0, scene = 1, menu, scores, options, pause, gameover };

typedef std::vector<std::unique_ptr<Text>> VecText;

class TextManager
{
public:
	TextManager();
	virtual ~TextManager();

	void initalize(textType tt, TTF_Font* font, SDL_Renderer* renderer);
	void update(textType tt, std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);

	void render(textType tt, SDL_Renderer* renderer);
	void exterminate();
	void exterminate(textType tt);

	textType actualTextType;
private:
	//vectors of Text objects
	VecText sceneTexts, menuTexts, scoresTexts, optTexts, pauseTexts, gameoverTexts;

	OverworldRandomizer overand;		//randomizer

	void initalizeTextScene(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextMenu(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextPause(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextOptions(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextHiscores(TTF_Font* font, SDL_Renderer* renderer);
	void initalizeTextGameOver(TTF_Font* font, SDL_Renderer* renderer);
	void updateTextScene(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);
	void updateTextMenu(TTF_Font* font, SDL_Renderer* renderer, bool isGraying = true);
	void updateTextOptions(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);
	void updateTextHiscores(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);

	SDL_Color greyColor(SDL_Color oldColor);
	SDL_Color ungreyColor(SDL_Color oldColor);
};

