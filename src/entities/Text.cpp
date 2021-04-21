#include "..\..\include\entities\Text.h"

Text::Text() : Graph(), txt(std::string()), txtColor(), isLeftside(true), alignX(0) {}

Text::Text(int x, int y) : Graph(x, y), txt(std::string()), txtColor(), isLeftside(true), alignX(x) {}

Text::Text(int x, int y, bool isLeftside) : Graph(x, y), txt(std::string()), txtColor(), isLeftside(isLeftside), alignX(x) {}

Text::~Text() {}

//load text from string, color and font
bool Text::loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
	//save information about string and color
	txt = textureText;
	txtColor = textColor;
	//make a graphic object based on text and returned a success status
	return Graph::loadFromText(alignX, textureText, textColor, renderer, font, isLeftside);
}

//Set new string of text
void Text::setText(std::string newTxt) { this->txt = newTxt; }

//Return a variable of text (string, color)
std::string& Text::getText() { return this->txt; }

SDL_Color Text::getColor() { return txtColor; }
