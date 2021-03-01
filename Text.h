#pragma once

#include "Graph.h"

class Text : public Graph
{
public:
	Text();
	Text(int x, int y);
	Text(int x, int y, bool isLeftside);
	virtual ~Text();

	bool loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font);

	void setText(std::string newTxt);
	std::string& getText();
	SDL_Color getColor();
private:
	std::string txt;			//text string
	SDL_Color txtColor;			//text color
	bool isLeftside;			//flag for text aligning, true when is align to left, false when is align to right
	int alignX;					//used for right aligning
};

