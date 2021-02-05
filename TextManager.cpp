#include "TextManager.h"

TextManager::TextManager() : texts(), overand() {}

TextManager::~TextManager() { texts.~vector(); }

void TextManager::initalize(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor(), color4 = overand.randomColor();
	
	texts.push_back(std::make_unique<Text>(48, 416));					//0 - tekst od poziomu
	texts.back()->loadFromText("Poziom:", color1, renderer, font);
	//texts.push_back(std::make_unique<Text>(48, 472));					//0 - tekst od poziomu (0.4.1)
	//texts.back()->loadFromText("Poziom:", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 472));					//1 - tekst od wyniku
	texts.back()->loadFromText("Wynik:", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 528));					//2 - tekst od motywacji
	texts.back()->loadFromText("Motywacja:", color2, renderer, font);
	//texts.push_back(std::make_unique<Text>(48, 528));					//1 - tekst od wyniku (w przysz³oœci)
	//texts.back()->loadFromText("Wynik:", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 584));					//3 - tekst od znalezisk
	texts.back()->loadFromText("Do znalezienia:", color3, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 416, false));			//4 - tekst od poziomu
	texts.back()->loadFromText("0", color1, renderer, font);
	//texts.push_back(std::make_unique<Text>(536, 472, false));			//4 - tekst od poziomu (0.4.1)
	//texts.back()->loadFromText("0", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 472, false));			//5 - tekst od wyniku
	texts.back()->loadFromText("-10", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 528, false));			//6 - tekst od motywacji
	texts.back()->loadFromText("100", color2, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 640));					//7 - tekst od instrukcji
	texts.back()->loadFromText(u8"[P] - instrukcja sterowania", color3, renderer, font);
}

void TextManager::update(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	//if (index > 2 && index < texts.size())		//do wersji 0.4.1
	if (index > 3 && index < texts.size() - 1)		//od wersji 0.5
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
