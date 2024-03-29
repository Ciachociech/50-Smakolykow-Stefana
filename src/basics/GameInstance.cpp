#include "..\..\include\basics\GameInstance.h"
#include <iostream>

GameInstance::GameInstance() : actualScene(sceneState::splashscreen), lastScene(sceneState::splashscreen), actualKeyState(keyState::none) {}

GameInstance::~GameInstance() {}

//the very main function, initalize window, load media and manage app loop
void GameInstance::run()
{
	//if app initialization is failed
	if (!init()) { printf("Failed to initialize!\n"); }
	//otherwise
	else
	{
		//if loading media is failed
		if (!loadMedia()) { printf("Failed to load media!\n"); }
		//if everything until now is alright, go to main loop of game
		else { loop(); }
	}
	//when main loop is ended, close all resources
	close();
}

//initialzing main SDL variables and checking the result of operation
bool GameInstance::init()
{
	//if window initializating is not possible, return false (success flag)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	//otherwise create a window
	else
	{
		window = SDL_CreateWindow(windowNameEN.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//if window is not created, return false (success flag)
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		//otherwise create a renderer
		else
		{
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			//if window renderer is not created, return false (success flag)
			if (windowRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			//otherwise create surface and check ability to load a font
			else
			{
				//SDL_SetRenderDrawColor(windowRenderer, 32, 32, 32, 0xFF);
				windowSurface = SDL_GetWindowSurface(window);
				//if window surface is not created, return false (success flag)
				if (windowSurface == NULL)
				{
					printf("Window surface could not be created! SDL Error: %s\n", SDL_GetError());
					return false;
				}
				//if font is not initialized, return false (success flag)
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					return false;
				}
			}
		}
	}

	return true;							//if everything was alright returns true
}

//loading window icon and font
bool GameInstance::loadMedia()
{
	bool success = true;					//flag for showing a success of media loading, can be set to false when something goes wrong

	//loading game logo
	SDL_Surface* surface = IMG_Load(logoPath.c_str());
	//if file does not exist, return false (success flag)
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", logoPath.c_str(), SDL_GetError());
		return false;
	}
	//otherwise set icon from surface as a window icon
	else
	{
		SDL_SetWindowIcon(window, surface);
	}
	SDL_FreeSurface(surface);				//free surface

	//loading font => source - https://www.dafont.com/wash-your-hand.font
	font = TTF_OpenFont("Assets/fonts/NerkoOne-Regular.ttf", 32);
	//if font does not exist, return false (success flag)
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	Mix_Volume(-1, 64);						//MAX is 128
	if (!am.initAudios())
	{
		printf("Failed to load at least one wav file! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	SDL_SetWindowTitle(window, windowNamePL.c_str());

	return true;							//if everything was alright returns true
}

//closing and destroying window and its renderer
void GameInstance::close()
{
	SDL_DestroyRenderer(windowRenderer);	//call function for destroying renderer
	windowRenderer = NULL;					//set a pointer of renderer to NULL
	SDL_DestroyWindow(window);				//call function for destroying window
	window = NULL;							//set a pointer of window to NULL

	IMG_Quit();								//stop using sld image
	SDL_Quit();								//definetly close all sdl things
}

//function with initializing and handling loop
bool GameInstance::loop()
{
	bool quit = false;						//flag for showing a life of loop, can be set to true when the app is closed
	actualScene = sceneState::mainmenu;
	Uint32 frameTime;						//time counter for frame

	initMenu(mainMenu, textType::menu);
	initMenu(pauseMenu, textType::pause);
	initMenu(optionsMenu, textType::options);
	initMenu(hiscoresMenu, textType::scores);
	initMenu(gameOverMenu, textType::gameover);
	initMenu(enterNameMenu, textType::enterName);
	
	game.loadRenderer(windowRenderer);
	game.loadFont(font);
	game.loadSteering(&sterman);
	game.loadTexting(&txtm);
	game.loadDating(&dati);
	game.loadAudio(&am);
	game.loadScores(&scorman);

	//do unless quit is false
	while (!quit)
	{
		frameTime = SDL_GetTicks();				//set time for beginning current frame
		
		switch (actualScene)
		{
			case sceneState::splashscreen: { break; }
			case sceneState::mainmenu:
			{
				switch (mainMenu.loop())
				{
				case 1: { game.reset(); updateSceneState(sceneState::game); break; }
				case 2: 
				{ 
					txtm.update(textType::menu, "", 1, font, windowRenderer);
					dati.load(om);
					for (int i = 0; i < optionsMenu.getMaxOptions(); i++) 
					{ txtm.update(textType::options, om.getOptionValueString(i), i, font, windowRenderer); }
					updateSceneState(sceneState::options);
					break; 
				}
				case 3:
				{
					txtm.update(textType::menu, "", 1, font, windowRenderer);
					dati.load(scorman);
					showScore(true);
					updateSceneState(sceneState::highscores);
					break;
				}
				case -2: case 4: { quit = true; break; }
				case 0: default: { break; }
				}
				break;
			}
			case sceneState::game:
			{ 
				switch (game.loop())
				{
					case -2: { quit = true; break; }
					case -1: 
					{ 
						updateSceneState(sceneState::pausemenu); 
						dati.load(om);
						break; 
					}
					case -3: {
						txtm.update(textType::gameover, "Wynik: " + std::to_string(scorman.getActualScore().getScore()), 0, font, windowRenderer);
						txtm.update(textType::gameover, "Poziom: " + std::to_string(game.getLevel()), 1, font, windowRenderer);
						txtm.update(textType::gameover, u8"Smako�yki: " + std::to_string(game.getFoundSnacks()), 2, font, windowRenderer);
						updateSceneState(sceneState::gameover);
						break;
					}
					case -4: {
						txtm.update(textType::gameover, "Wynik: " + std::to_string(scorman.getActualScore().getScore()), 0, font, windowRenderer);
						txtm.update(textType::gameover, "Poziom: " + std::to_string(game.getLevel()), 1, font, windowRenderer);
						txtm.update(textType::gameover, u8"Smako�yki: " + std::to_string(game.getFoundSnacks()), 2, font, windowRenderer);
						enterNameMenu.setEditableString(scorman.getPlayerName());
						updateSceneState(sceneState::entermenu);
						break;
					}
					case 0: default: { break; }
				}
				break;
			}
			case sceneState::highscores: 
			{
				switch (hiscoresMenu.loop())
				{
					case -1:
					{
						txtm.update(textType::menu, "", 0, font, windowRenderer);
						updateSceneState(lastScene);
						break;
					}
					case -4:
					{
						showScore(scorman.decrementPlace());
						break;
					}
					case -6:
					{
						showScore(scorman.incrementPlace());
						break;
					}
				}
				break; 
			}
			case sceneState::options: 
			{ 
				switch (optionsMenu.loop())
				{
					case -1: 
					{ 
						txtm.update(textType::menu, "", 0, font, windowRenderer); 
						updateSceneState(lastScene); 
						dati.save(om);
						appendOptions();
						break; 
					}
					case -4: 
					{ 
						om.decreaseOptionValue(optionsMenu.getActualOption()); 
						txtm.update(textType::options, om.getOptionValueString(optionsMenu.getActualOption()), optionsMenu.getActualOption(), font, windowRenderer);
						break; 
					}
					case -6: 
					{ 
						om.increaseOptionValue(optionsMenu.getActualOption()); 
						txtm.update(textType::options, om.getOptionValueString(optionsMenu.getActualOption()), optionsMenu.getActualOption(), font, windowRenderer);
						break; 
					}
					default: { break; }
				}
			}
			case sceneState::pausemenu: 
			{ 
				switch (pauseMenu.loop())
				{
				case -2: { quit = true; break; }
				case 1: { updateSceneState(sceneState::game); break; }
				case 2: 
				{ 
					txtm.update(textType::menu, "", 1, font, windowRenderer); 
					dati.load(om);
					for (int i = 0; i < optionsMenu.getMaxOptions(); i++)
					{
						txtm.update(textType::options, om.getOptionValueString(i), i, font, windowRenderer);
					}
					updateSceneState(sceneState::options); 
					break; 
				}
				case 3: { updateSceneState(sceneState::mainmenu); break; }
				case 0: default: { break; }
				}
				break;
			}
			case sceneState::gameover:
			{
				switch (gameOverMenu.loop())
				{
				case -2: { quit = true; break; }
				case 1: { game.reset(); updateSceneState(sceneState::game); break; }
				case 2: { updateSceneState(sceneState::mainmenu); break; }
				case 0: default: { break; }

				}
				break;
			}
			case sceneState::entermenu:
			{
				txtm.update(textType::enterName, enterNameMenu.getEditableString() + "_", 1, font, windowRenderer);
				switch (enterNameMenu.loop())
				{
				case -2: { quit = true; break; }
				case -1: 
				{ 
					txtm.update(textType::gameover, "Wynik: " + std::to_string(scorman.getActualScore().getScore()), 0, font, windowRenderer);
					txtm.update(textType::gameover, "Poziom: " + std::to_string(game.getLevel()), 1, font, windowRenderer);
					txtm.update(textType::gameover, u8"Smako�yki: " + std::to_string(game.getFoundSnacks()), 2, font, windowRenderer);
					updateSceneState(sceneState::gameover); 
					break; 
				}
				case 1: 
				{
					scorman.setPlayerName(enterNameMenu.getEditableString());
					dati.save(scorman.saveActualScore(game.getLevel(), game.getFoundSnacks()));
					updateSceneState(sceneState::gameover);
					break; 
				}
				case 0: case 2: default: { break; }
				}
				break;
			}
			default: { break; }
		}
		render();

		//std::cout << "FPS: " << 1000 / (SDL_GetTicks() - frameTime) << std::endl;

		//if current frame time is less than 1000/16.7 ms, wait the time difference (to have more stable 60 FPS)
		if ((SDL_GetTicks() - frameTime) < (1000.f / FPS)) { SDL_Delay((1000.f / FPS) - (SDL_GetTicks() - frameTime)); }
	}

	return true;
}

//depending of program state, render objects on window
void GameInstance::render()
{
	SDL_RenderClear(windowRenderer);		//clear all previous renedered objects
	switch (actualScene)
	{
		case sceneState::splashscreen: { break; }
		case sceneState::mainmenu: { mainMenu.render(textType::menu); break; }
		case sceneState::game: { game.render(); break; }
		case sceneState::highscores: { mainMenu.render(textType::menu); hiscoresMenu.render(textType::scores); break; }
		case sceneState::options: 
		{ 
			switch (lastScene)
			{
				case sceneState::mainmenu: { mainMenu.render(textType::menu); break; }
				case sceneState::pausemenu: { game.renderScene(); break; }
				default: { break; }
			}
			optionsMenu.render(textType::options); 
			break; 
		}
		case sceneState::pausemenu: { game.renderScene(); pauseMenu.render(textType::pause); break; }
		case sceneState::gameover: { game.renderScene(); gameOverMenu.render(textType::gameover); break; }
		case sceneState::entermenu: { game.renderScene(); enterNameMenu.render(textType::enterName); break; }
		default: { break; }
	}
	SDL_RenderPresent(windowRenderer);		//window updating
}

//update actual scene state, but notice the last one too
void GameInstance::updateSceneState(sceneState newState)
{
	lastScene = actualScene;
	actualScene = newState;
}

//change sound volume depending on newest audio options
void GameInstance::appendOptions()
{
	am.setMusicVolume(om.getOptionValue(0));
	am.setEffectVolume(om.getOptionValue(1));
}

//initialize and append objects to selected menu
void GameInstance::initMenu(GameMenu& menu, textType tt)
{
	menu.loadRenderer(windowRenderer);
	menu.loadFont(font);
	menu.loadSteering(&sterman);
	menu.loadTexting(&txtm);
	menu.init(tt);
}

//show score depending of actual place
bool GameInstance::showScore(bool success)
{
	if (success)
	{
		HistoryScore hiscore = scorman.getBestScore(scorman.getShownPlace());
		txtm.update(textType::scores, "Rezultat - miejsce " + std::to_string(scorman.getShownPlace() + 1), 0, font, windowRenderer);
		if (hiscore.getNickname() == "/NONAME/" || hiscore.getNickname() == "Stefan")
		{
			txtm.update(textType::scores, " ", 1, font, windowRenderer);
			txtm.update(textType::scores, " ", 7, font, windowRenderer);
		}
		else
		{
			txtm.update(textType::scores, "Nick:", 1, font, windowRenderer);
			txtm.update(textType::scores, hiscore.getNickname(), 7, font, windowRenderer);
		}
		txtm.update(textType::scores, std::to_string(hiscore.getScore()), 8, font, windowRenderer);
		txtm.update(textType::scores, std::to_string(hiscore.getGainedLevel()), 9, font, windowRenderer);
		txtm.update(textType::scores, std::to_string(hiscore.getCollectedTidbits()), 10, font, windowRenderer);
		txtm.update(textType::scores, hiscore.getDate(), 11, font, windowRenderer);
		txtm.update(textType::scores, hiscore.getVersion(), 12, font, windowRenderer);
		return true;
	}
	return false;
}
