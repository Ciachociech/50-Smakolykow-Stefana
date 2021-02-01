#include "Text.h"

Text::Text() : Graph(), txt(std::string()), txtColor(), isLeftside(true) {}

Text::Text(int x, int y) : Graph(x, y), txt(std::string()), txtColor(), isLeftside(true) {}

Text::Text(int x, int y, bool isLeftside) : Graph(x, y), txt(std::string()), txtColor(), isLeftside(isLeftside) {}

Text::~Text() {}

bool Text::loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
	txt = textureText;
	txtColor = textColor;
	return Graph::loadFromText(textureText, textColor, renderer, font, isLeftside);
}

void Text::setText(std::string newTxt) { this->txt = newTxt; }

std::string& Text::getText() { return this->txt; }

SDL_Color Text::getColor() { return txtColor; }
