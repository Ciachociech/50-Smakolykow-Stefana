#include "..\..\include\managers\TextManager.h"

TextManager::TextManager() : actualTextType(textType::none), sceneTexts(), menuTexts(), scoresTexts(), optTexts(), pauseTexts(), overand() {}

TextManager::~TextManager() 
{ 
	exterminate();
	sceneTexts.~vector(); 
	menuTexts.~vector();
	scoresTexts.~vector();
	optTexts.~vector();
	pauseTexts.~vector();
}

//initializes all Text objects
void TextManager::initalizeTextScene(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor(), color4 = overand.randomColor();
	
	sceneTexts.push_back(std::make_unique<Text>(102, 224));					//0 - const motivation text
	sceneTexts.back()->loadFromText("Motywacja", color2, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(353, 224));					//1 - const instinct text
	sceneTexts.back()->loadFromText("Instynkt", overand.randomColor(), renderer, font);

	sceneTexts.push_back(std::make_unique<Text>(226, 354, false));			//2 - non-const motivation text
	sceneTexts.back()->loadFromText("100", color2, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(3300, 3580, false));		//3 - non-const unused text
	sceneTexts.back()->loadFromText("100", overand.randomColor(), renderer, font);

	sceneTexts.push_back(std::make_unique<Text>(48, 416));					//4 - const level text
	sceneTexts.back()->loadFromText("Poziom:", color1, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(48, 472));					//5 - const score text
	sceneTexts.back()->loadFromText("Wynik:", color3, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(48, 528));					//6 - const best score text
	sceneTexts.back()->loadFromText("Rekord:", color4, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(48, 584));					//7 - const treasure text
	sceneTexts.back()->loadFromText("Do znalezienia:", overand.randomColor(), renderer, font);

	sceneTexts.push_back(std::make_unique<Text>(536, 416, false));			//8 - non-const level text
	sceneTexts.back()->loadFromText("0", color1, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(536, 472, false));			//9 - non-const score text
	sceneTexts.back()->loadFromText("-10", color3, renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(536, 528, false));			//10 - non-const score text
	sceneTexts.back()->loadFromText("-10", color4, renderer, font);

	sceneTexts.push_back(std::make_unique<Text>(48, 640));					//11 - const help text
	sceneTexts.back()->loadFromText(u8"[P] - instrukcja sterowania", overand.randomColor(), renderer, font);
}

void TextManager::initalizeTextMenu(TTF_Font* font, SDL_Renderer* renderer)
{
	menuTexts.push_back(std::make_unique<Text>(1152, 360, false));			//0 - new game text
	menuTexts.back()->loadFromText("Nowa gra", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(1152, 416, false));			//1 - hi-scores text
	menuTexts.back()->loadFromText("0123456789", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(1152, 472, false));			//2 - options text
	menuTexts.back()->loadFromText(u8"Êœ¹æ¿", overand.randomColor(), renderer, font);
	/*
	sceneTexts.push_back(std::make_unique<Text>(1152, 528, false));			//3 - future text
	sceneTexts.back()->loadFromText("???", overand.randomColor(), renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(1152, 584, false));			//4 - future text
	sceneTexts.back()->loadFromText("???", overand.randomColor(), renderer, font);
	sceneTexts.push_back(std::make_unique<Text>(1152, 630, false));			//5 - exit text
	sceneTexts.back()->loadFromText("???", overand.randomColor(), renderer, font);
	*/
	menuTexts.push_back(std::make_unique<Text>(1152, 528, false));			//3 - exit text
	menuTexts.back()->loadFromText(u8"Wyjœcie z gry", overand.randomColor(), renderer, font);
	
	menuTexts.push_back(std::make_unique<Text>(1216, 640, false));			//4 - exit text
	menuTexts.back()->loadFromText(u8"Wersja 0.9.3 - by Ciachociech", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(48, 584));					//5 - const help1 text
	menuTexts.back()->loadFromText(u8"[W/S] - wybór opcji", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(48, 640));					//6 - const help1 text
	menuTexts.back()->loadFromText(u8"[ENTER] - zatwierdzenie opcji", overand.randomColor(), renderer, font);
}

void TextManager::initalizeTextPause(TTF_Font* font, SDL_Renderer* renderer)
{
	pauseTexts.push_back(std::make_unique<Text>(112, 360));				//0 - new game text
	pauseTexts.back()->loadFromText(u8"Powrót do gry", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(112, 416));				//1 - hi-scores text
	pauseTexts.back()->loadFromText("0123456789", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(112, 472));				//2 - options text
	pauseTexts.back()->loadFromText(u8"WyjdŸ do menu", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(48, 248));				//3 - pause text
	pauseTexts.back()->loadFromText("Pauza", overand.randomColor(), renderer, font);

	pauseTexts.push_back(std::make_unique<Text>(48, 584));				//4 - const help1 text
	pauseTexts.back()->loadFromText(u8"[W/S] - wybór opcji", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(48, 640));				//5 - const help1 text
	pauseTexts.back()->loadFromText(u8"[ENTER] - zatwierdzenie opcji", overand.randomColor(), renderer, font);
}

void TextManager::updateTextScene(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	//if index is valid
	if (index == 2 || index == 3 || (index > 7 && index < sceneTexts.size() - 1))		//since version 0.5
	{
		sceneTexts[index]->loadFromText(newValue, sceneTexts[index]->getColor(), renderer, font);
	}
}

void TextManager::updateTextMenu(TTF_Font* font, SDL_Renderer* renderer, bool isGraying)
{
	for (int i = 0; i < menuTexts.size(); i++) 
	{ 
		sceneTexts[i]->loadFromText(menuTexts[i]->getText(), (isGraying?greyColor(menuTexts[i]->getColor()): ungreyColor(menuTexts[i]->getColor())), renderer, font);
	}
}

SDL_Color TextManager::greyColor(SDL_Color oldColor)
{
	SDL_Color newColor;
	newColor.r = oldColor.r - 128;
	newColor.g = oldColor.g - 128;
	newColor.b = oldColor.b - 128;
	newColor.a = oldColor.a;
	return newColor;
}

SDL_Color TextManager::ungreyColor(SDL_Color oldColor)
{
	SDL_Color newColor;
	newColor.r = oldColor.r + 128;
	newColor.g = oldColor.g + 128;
	newColor.b = oldColor.b + 128;
	newColor.a = oldColor.a;
	return newColor;
}

//initializes all Text objects
void TextManager::initalize(textType tt, TTF_Font* font, SDL_Renderer* renderer)
{
	switch (tt)
	{
	case textType::scene: { initalizeTextScene(font, renderer); break; }
	case textType::menu: { initalizeTextMenu(font, renderer); break; }
	case textType::scores: {  break; }
	case textType::options: {  break; }
	case textType::pause: { initalizeTextPause(font, renderer); break; }
	default: { break; }
	}
}

//change certain text by changing string and font
void TextManager::update(textType tt, std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	switch (tt)
	{
	case textType::scene: { updateTextScene(newValue, index, font, renderer); break; }
	case textType::menu: 
	{ 

		if (index != 0) { updateTextMenu(font, renderer); }
		else { updateTextMenu(font, renderer, false); }
		break; 
	}
	case textType::scores: {  break; }
	case textType::options: {  break; }
	case textType::pause: { break; }
	default: { break; }
	}
}

//render all Text objects
void TextManager::render(textType tt, SDL_Renderer* renderer)
{
	switch (tt)
	{
	case textType::scene: { for (int i = 0; i < sceneTexts.size(); i++) { sceneTexts[i]->render(renderer); } break; }
	case textType::menu: { for (int i = 0; i < menuTexts.size(); i++) { menuTexts[i]->render(renderer); } break; }
	case textType::scores: {  break; }
	case textType::options: {  break; }
	case textType::pause: { for (int i = 0; i < pauseTexts.size(); i++) { pauseTexts[i]->render(renderer); } break; }
	default: { break; }
	}
}

//remove all Text objects
void TextManager::exterminate()
{
	sceneTexts.clear();
	menuTexts.clear();
	scoresTexts.clear();
	optTexts.clear();
	pauseTexts.clear();
}

//remove all scene Text objects
void TextManager::exterminate(textType tt) 
{ 
	switch (tt)
	{
		case textType::scene: { sceneTexts.clear(); break; }
		case textType::menu: { menuTexts.clear(); break; }
		case textType::scores: { scoresTexts.clear(); break; }
		case textType::options: { optTexts.clear(); break; }
		case textType::pause: { pauseTexts.clear(); break; }
		default: { break; }
	}
}
