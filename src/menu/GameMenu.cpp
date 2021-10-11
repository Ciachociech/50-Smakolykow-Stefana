#include "..\..\include\menu\GameMenu.h"

//loop for standard menu
int GameMenu::menuLoop()
{
	SDL_Event event;							//sdl event variable for observing keyboard action or game exiting
	keyAction actualAction = keyAction::none;	//reseting action information

	//when the event is performed
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		//app closing
		case SDL_QUIT: { return -2; break; }
		//key pressing
		case SDL_KEYDOWN: { actualAction = sterman->keyboardMenu(event.key.keysym.sym); break; }
		default: { break; }
		}
	}

	if (actualAction != keyAction::none) { SDL_Delay(100); }

	int cursorY = cursor.Y();

	switch (actualAction)
	{
	case keyAction::prevMenu: { actualOption--; cursorY -= 56; break; }
	case keyAction::nextMenu: { actualOption++; cursorY += 56; break; }
	case keyAction::lessMenu: { return -4; break; }
	case keyAction::moreMenu: { return -6; break; }
	case keyAction::enterMenu:
	{
		int returnOption = actualOption + 1;
		cursor.setXY(cursor.X(), cursor.Y() - 56 * actualOption);
		actualOption = 0;
		return returnOption; break;
	}
	case keyAction::goBackMenu: { return -1; break; }
	default: { break; }
	}

	if (actualOption == -1) { actualOption++; cursorY += 56; }
	else if (actualOption == maxOptions) { actualOption--; cursorY -= 56; }

	cursor.setXY(cursor.X(), cursorY);

	return 0;
}

//loop for menu with text entering
int GameMenu::enterLoop()
{
	SDL_Event event;							//sdl event variable for observing keyboard action or game exiting
	keyAction actualAction = keyAction::none;	//reseting action information

	SDL_StartTextInput();

	//when the event is performed
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		//app closing
		case SDL_QUIT: { return -2; break; }
		//key pressing
		case SDL_KEYDOWN: case SDL_TEXTINPUT: { actualAction = sterman->keyboardString(editableString, event); break; }
		default: { break; }
		}
	}

	SDL_StopTextInput();

	if (actualAction != keyAction::none) { SDL_Delay(100); }
	switch (actualAction)
	{
	case keyAction::acceptName: { return 1; break; }
	case keyAction::rejectName: { return -1; break; }
	case keyAction::backspaceName: { return 2; break; }
	}

	return 0;
}

GameMenu::GameMenu() : overand(), maxOptions(0), isEntering(false) {}

GameMenu::GameMenu(int optionsCount) : overand(), maxOptions(optionsCount < 0 ? -optionsCount : optionsCount), isEntering(optionsCount < 0 ? true : false) {}

GameMenu::~GameMenu() { close(); }

void GameMenu::loadRenderer(SDL_Renderer* rend) { this->windowRenderer = rend; }

void GameMenu::loadFont(TTF_Font* font) { this->font = font; }

void GameMenu::loadSteering(SteeringManager* sm) { this->sterman = sm; }

void GameMenu::loadTexting(TextManager* tm) { this->txtm = tm; }

//loop depending of menu type
int GameMenu::loop()
{
	if (isEntering) { return enterLoop(); }
	else { return menuLoop(); }
}

//initialize depending of text/menu type
void GameMenu::init(textType tt)
{
	//text manager reseting (font and text)
	txtm->exterminate(tt);
	txtm->initalize(tt, font, windowRenderer);

	switch (tt)
	{
		case textType::menu: 
		{
			logo = Graph(712, 64);
			logo.loadFromFile(1.f, 1.f, "Assets/panel/ingameLogoPL.png", windowRenderer);
			cursor = Graph(1184, 364);
			cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandP.png", windowRenderer);
			break;
		}
		case textType::pause: 
		case textType::options:
		{
			cursor = Graph(48, 308);
			cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandL.png", windowRenderer);
			break;
		}
		case textType::gameover:
		{
			cursor = Graph(48, 416);
			cursor.loadFromFile(1.f, 1.f, "Assets/menu/secretHandL.png", windowRenderer);
			break;
		}
		default: { break; }
	}
}

//dereference all objects
void GameMenu::close()
{
	font = NULL;
	sterman = NULL;
	txtm = NULL;
}

//render object of menu
void GameMenu::render(textType tt)
{
	txtm->render(tt, windowRenderer);						//render all text graphs
	if (logo.X() != 0 && logo.Y() != 0) { logo.render(windowRenderer); }
	if (cursor.X() != 0 && cursor.Y() != 0) { cursor.render(windowRenderer); }
}

int GameMenu::getActualOption() { return actualOption; }

int GameMenu::getMaxOptions() { return maxOptions; }

std::string GameMenu::getEditableString() { return editableString; }

void GameMenu::setEditableString(std::string editableString) { this->editableString = editableString; }
