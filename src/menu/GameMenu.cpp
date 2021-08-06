#include "..\..\include\menu\GameMenu.h"

GameMenu::GameMenu() : overand(), maxOptions(0) {}

GameMenu::GameMenu(int optionsCount) : overand(), maxOptions(optionsCount) {}

GameMenu::~GameMenu() { close(); }

void GameMenu::loadRenderer(SDL_Renderer* rend) { this->windowRenderer = rend; }

void GameMenu::loadFont(TTF_Font* font) { this->font = font; }

void GameMenu::loadSteering(SteeringManager* sm) { this->sterman = sm; }

void GameMenu::loadTexting(TextManager* tm) { this->txtm = tm; }

int GameMenu::loop()
{
	SDL_Event event;						//sdl event variable for observing keyboard action or game exiting
	keyAction actualAction = keyAction::none;	//reseting action information

	//when the event is performed
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		//app closing
		case SDL_QUIT: { return -2; break; }
		//key pressing
		case SDL_KEYDOWN:{ actualAction = sterman->keyboardMenu(event.key.keysym.sym); break; }
		default: { break; }
		}
	}	

	if (actualAction != keyAction::none) { SDL_Delay(100); }

	int cursorY = cursor.Y();

	switch (actualAction)
	{
	case keyAction::prev: { actualOption--; cursorY -= 56; break; }
	case keyAction::next: { actualOption++; cursorY += 56; break; }
	case keyAction::less: { return -4; break; }
	case keyAction::more: { return -6; break; }
	case keyAction::enter: 
	{
		int returnOption = actualOption + 1;
		cursor.setXY(cursor.X(), cursor.Y() - 56 * actualOption);
		actualOption = 0;
		return returnOption; break; 
	}
	case keyAction::goBack: { return -1; break; }
	default: { break; }
	}

	if (actualOption == -1) { actualOption++; cursorY += 56; }
	else if (actualOption == maxOptions) { actualOption--; cursorY -= 56; }

	cursor.setXY(cursor.X(), cursorY);

	return 0;
}

void GameMenu::init(textType tt)
{
	//text manager reseting (font and text)
	txtm->exterminate(tt);
	txtm->initalize(tt, font, windowRenderer);

	if (tt == textType::menu)
	{
		logo = Graph(712, 64);
		logo.loadFromFile(1.f, 1.f, "Assets/panel/ingameLogoPL.png", windowRenderer);
		cursor = Graph(1184, 364);
		cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandP.png", windowRenderer);
	}

	if (tt == textType::pause)
	{
		cursor = Graph(48, 308);
		cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandL.png", windowRenderer);
	}

	if (tt == textType::options)
	{
		cursor = Graph(48, 308);
		cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandL.png", windowRenderer);
	}
}

void GameMenu::close()
{
	font = NULL;
	sterman = NULL;
	txtm = NULL;
}

void GameMenu::render(textType tt)
{
	txtm->render(tt, windowRenderer);						//render all text graphs
	if (logo.X() != 0 && logo.Y() != 0) { logo.render(windowRenderer); }
	if (cursor.X() != 0 && cursor.Y() != 0) { cursor.render(windowRenderer); }
}

int GameMenu::getActualOption() { return actualOption; }

int GameMenu::getMaxOptions() { return maxOptions; }
