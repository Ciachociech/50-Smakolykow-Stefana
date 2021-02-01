#include "TextManager.h"

TextManager::TextManager() : texts(), overand() {}

TextManager::~TextManager() { texts.~vector(); }

void TextManager::initalize(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor();
	
	texts.push_back(std::make_unique<Text>(48, 472));
	texts.back()->loadFromText("Poziom:", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 528));
	texts.back()->loadFromText("Motywacja:", color2, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 584));
	texts.back()->loadFromText("Kafelki do odkrycia:", color3, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 472, false));
	texts.back()->loadFromText("0", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 528, false));
	texts.back()->loadFromText("-1:", color2, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 584, false));
	texts.back()->loadFromText("-1", color3, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 640));
	texts.back()->loadFromText(u8"[P] - instrukcja sterowania", color3, renderer, font);
}

void TextManager::update(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	if (index > 2 && index < texts.size())
	{
		texts[index]->loadFromText(newValue, texts[index]->getColor(), renderer, font);
	}
}

void TextManager::render(SDL_Renderer* renderer) 
{
	for (int i = 0; i < texts.size(); i++) { texts[i]->render(renderer); }
}

void TextManager::exterminate()
{
	texts.clear();
}
