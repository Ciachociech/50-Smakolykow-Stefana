#pragma once

#include "..\external_dependencies.h"

#include "..\entities\Text.h"
#include "..\basics\OverworldRandomizer.h"

typedef std::vector<std::unique_ptr<Text>> VecText;

class TextManager
{
public:
	TextManager();
	virtual ~TextManager();

	void initalize(TTF_Font* font, SDL_Renderer* renderer);
	void update(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);
	void exterminate();
private:
	VecText texts;						//vector of Text objects
	OverworldRandomizer overand;		//randomizer
};

