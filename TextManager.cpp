#include "TextManager.h"

TextManager::TextManager() : texts(), overand() {}

TextManager::~TextManager() { texts.~vector(); }

//initializes all Text objects
void TextManager::initalize(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor(), color4 = overand.randomColor();
	
	texts.push_back(std::make_unique<Text>(206, 224));					//0 - const motivation text
	texts.back()->loadFromText("Motywacja", color2, renderer, font);
	texts.push_back(std::make_unique<Text>(2060, 2240));				//1 - const future text
	texts.back()->loadFromText("Motywacja", color2, renderer, font);

	texts.push_back(std::make_unique<Text>(330, 358, false));			//2 - non-const motivation text
	texts.back()->loadFromText("100", color2, renderer, font);
	texts.push_back(std::make_unique<Text>(3300, 3580, false));			//3 - non-const future text
	texts.back()->loadFromText("100", color2, renderer, font);

	texts.push_back(std::make_unique<Text>(48, 416));					//4 - const level text
	texts.back()->loadFromText("Poziom:", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 472));					//5 - const score text
	texts.back()->loadFromText("Wynik:", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 528));					//6 - const best score text
	texts.back()->loadFromText("Rekord:", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(48, 584));					//7 - const treasure text
	texts.back()->loadFromText("Do znalezienia:", color3, renderer, font);

	texts.push_back(std::make_unique<Text>(536, 416, false));			//8 - non-const level text
	texts.back()->loadFromText("0", color1, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 472, false));			//9 - non-const score text
	texts.back()->loadFromText("-10", color4, renderer, font);
	texts.push_back(std::make_unique<Text>(536, 528, false));			//10 - non-const score text
	texts.back()->loadFromText("-10", color4, renderer, font);

	texts.push_back(std::make_unique<Text>(48, 640));					//11 - const help text
	texts.back()->loadFromText(u8"[P] - instrukcja sterowania", color3, renderer, font);
}

//change certain text by changing string and font
void TextManager::update(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	//if index is valid
	if (index == 2 || index == 3 || (index > 7 && index < texts.size() - 1))		//since version 0.5
	{
		texts[index]->loadFromText(newValue, texts[index]->getColor(), renderer, font);
	}
}

//render all Text objects
void TextManager::render(SDL_Renderer* renderer) 
{
	for (int i = 0; i < texts.size(); i++) { texts[i]->render(renderer); }
}

//remove all Text objects
void TextManager::exterminate()
{
	texts.clear();
}
