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
	menuTexts.back()->loadFromText("Opcje", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(1152, 472, false));			//2 - options text
	menuTexts.back()->loadFromText(u8"Wyniki", overand.randomColor(), renderer, font);
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
	
	menuTexts.push_back(std::make_unique<Text>(1216, 640, false));			//4 - version text
	menuTexts.back()->loadFromText(u8"Wersja 0.10 - by Ciachociech", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(48, 584));					//5 - const help1 text
	menuTexts.back()->loadFromText(u8"[W/S] - wybór opcji", overand.randomColor(), renderer, font);
	menuTexts.push_back(std::make_unique<Text>(48, 640));					//6 - const help1 text
	menuTexts.back()->loadFromText(u8"[ENTER] - zatwierdzenie opcji", overand.randomColor(), renderer, font);
}

void TextManager::initalizeTextPause(TTF_Font* font, SDL_Renderer* renderer)
{
	pauseTexts.push_back(std::make_unique<Text>(112, 304));				//0 - new game text
	pauseTexts.back()->loadFromText(u8"Powrót do gry", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(112, 360));				//1 - hi-scores text
	pauseTexts.back()->loadFromText("Opcje", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(112, 416));				//2 - options text
	pauseTexts.back()->loadFromText(u8"WyjdŸ do menu", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(48, 248));				//3 - pause title text
	pauseTexts.back()->loadFromText("Pauza", overand.randomColor(), renderer, font);

	pauseTexts.push_back(std::make_unique<Text>(48, 584));				//4 - const help1 text
	pauseTexts.back()->loadFromText(u8"[W/S] - wybór opcji", overand.randomColor(), renderer, font);
	pauseTexts.push_back(std::make_unique<Text>(48, 640));				//5 - const help2 text
	pauseTexts.back()->loadFromText(u8"[ENTER] - zatwierdzenie opcji", overand.randomColor(), renderer, font);
}

void TextManager::initalizeTextOptions(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor();

	optTexts.push_back(std::make_unique<Text>(48, 248));				//0 - options title text
	optTexts.back()->loadFromText("Opcje", overand.randomColor(), renderer, font);
	optTexts.push_back(std::make_unique<Text>(112, 304));				//1 - music volume text
	optTexts.back()->loadFromText(u8"G³oœnoœæ muzyki", color1, renderer, font);
	optTexts.push_back(std::make_unique<Text>(112, 360));				//2 - effect volume text
	optTexts.back()->loadFromText(u8"G³oœnoœæ efektów", color2, renderer, font);
	//optTexts.push_back(std::make_unique<Text>(112, 416));				//3 - future option text
	//optTexts.back()->loadFromText("Opcje", color3, renderer, font);

	optTexts.push_back(std::make_unique<Text>(512, 304, false));		//3 - music volume value text
	optTexts.back()->loadFromText("100%", color1, renderer, font);
	optTexts.push_back(std::make_unique<Text>(512, 360, false));		//4 - effect volume value text
	optTexts.back()->loadFromText("100%", color2, renderer, font);
	//optTexts.push_back(std::make_unique<Text>(600, 416, false));		//5 - hi-scores text
	//optTexts.back()->loadFromText("Opcje", color3, renderer, font);

	optTexts.push_back(std::make_unique<Text>(48, 528));				//5 - const help1 text
	optTexts.back()->loadFromText(u8"[W/S] - wybór opcji", overand.randomColor(), renderer, font);
	optTexts.push_back(std::make_unique<Text>(48, 584));				//6 - const help2 text
	optTexts.back()->loadFromText(u8"[A/D] - zmiana wartoœci", overand.randomColor(), renderer, font);
	optTexts.push_back(std::make_unique<Text>(48, 640));				//7 - const help3 text
	optTexts.back()->loadFromText(u8"[ESC] - wyjœcie do g³ównego menu", overand.randomColor(), renderer, font);
}

void TextManager::initalizeTextHiscores(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Color	color1 = overand.randomColor(), color2 = overand.randomColor(), color3 = overand.randomColor(), color4 = overand.randomColor(), 
				color5 = overand.randomColor();

	scoresTexts.push_back(std::make_unique<Text>(48, 192));				//0 - scores title text
	scoresTexts.back()->loadFromText("Najlepszy rezultat", overand.randomColor(), renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 248));				//1 - const score text
	scoresTexts.back()->loadFromText(u8"Wynik:", color1, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 304));				//2 - const level text
	scoresTexts.back()->loadFromText(u8"Poziom:", color2, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 360));				//3 - const tidbits text
	scoresTexts.back()->loadFromText(u8"Smako³yki:", color3, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 416));				//4 - const date text
	scoresTexts.back()->loadFromText(u8"Data:", color4, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 472));				//5 - const version text
	scoresTexts.back()->loadFromText(u8"Wersja:", color5, renderer, font);

	scoresTexts.push_back(std::make_unique<Text>(512, 248, false));		//6 - non-const score text
	scoresTexts.back()->loadFromText("0", color1, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(512, 304, false));		//7 - non-const level text
	scoresTexts.back()->loadFromText("1", color2, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(512, 360, false));		//8 - non-const tidbits text
	scoresTexts.back()->loadFromText("0", color3, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(512, 416, false));		//9 - non-const date text
	scoresTexts.back()->loadFromText("2021/08/06", color4, renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(512, 472, false));		//10 - non-const version text
	scoresTexts.back()->loadFromText("0.10", color5, renderer, font);

	//scoresTexts.push_back(std::make_unique<Text>(48, 584));			//11 - const help1 text
	//scoresTexts.back()->loadFromText(u8"[A/D] - poprzedni/nastêpny wynik", overand.randomColor(), renderer, font);
	scoresTexts.push_back(std::make_unique<Text>(48, 640));				//11 - const help2 text
	scoresTexts.back()->loadFromText(u8"[ESC] - wyjœcie do g³ównego menu", overand.randomColor(), renderer, font);
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
		menuTexts[i]->loadFromText(menuTexts[i]->getText(), (isGraying?greyColor(menuTexts[i]->getColor()): ungreyColor(menuTexts[i]->getColor())), renderer, font);
	}
	if (isGraying)
	{
		menuTexts[5]->setXY(2000, 2000);
		menuTexts[6]->setXY(2000, 2000);
	}
	else {
		menuTexts[5]->setXY(48, 584);
		menuTexts[6]->setXY(48, 640);
	}
}

void TextManager::updateTextOptions(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	//if index is valid
	if (index == 3 || index == 4)														//since version 0.10
	{
		optTexts[index]->loadFromText(newValue, optTexts[index]->getColor(), renderer, font);
	}
}

void TextManager::updateTextHiscores(std::string newValue, int index, TTF_Font* font, SDL_Renderer* renderer)
{
	//if index is valid
	if (index > 5 && index < 11)		//since version 0.10
	{
		scoresTexts[index]->loadFromText(newValue, scoresTexts[index]->getColor(), renderer, font);
	}
}

SDL_Color TextManager::greyColor(SDL_Color oldColor)
{
	SDL_Color newColor;
	newColor.r = oldColor.r - 64;
	newColor.g = oldColor.g - 64;
	newColor.b = oldColor.b - 64;
	newColor.a = oldColor.a - 128;
	return newColor;
}

SDL_Color TextManager::ungreyColor(SDL_Color oldColor)
{
	SDL_Color newColor;
	newColor.r = oldColor.r + 64;
	newColor.g = oldColor.g + 64;
	newColor.b = oldColor.b + 64;
	newColor.a = oldColor.a + 128;
	return newColor;
}

//initializes all Text objects
void TextManager::initalize(textType tt, TTF_Font* font, SDL_Renderer* renderer)
{
	switch (tt)
	{
	case textType::scene: { initalizeTextScene(font, renderer); break; }
	case textType::menu: { initalizeTextMenu(font, renderer); break; }
	case textType::scores: { initalizeTextHiscores(font, renderer); break; }
	case textType::options: { initalizeTextOptions(font, renderer); break; }
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
	case textType::scores: { updateTextHiscores(newValue, index, font, renderer); break; }
	case textType::options: { updateTextOptions(newValue, index + 3, font, renderer); break; }
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
	case textType::scores: { for (int i = 0; i < scoresTexts.size(); i++) { scoresTexts[i]->render(renderer); } break; }
	case textType::options: { for (int i = 0; i < optTexts.size(); i++) { optTexts[i]->render(renderer); } break; }
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
