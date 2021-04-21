#include "..\..\include\basics\GameInstance.h"

GameInstance::GameInstance() {}

GameInstance::~GameInstance() {}

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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	//otherwise create a window
	else
	{
		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	SDL_Event event;						//sdl event variable for observing keyboard action or game exiting

	gameInit();								//init game values

	int tileX, tileY;						//movement destination of player (Stefan) counted as tile width/height (x32 coord)
	Uint32 frameTime;						//time counter for frame
	keyAction actualAction;					//shows information about last chosen action (by keyboard)

	//do unless quit is false
	while (!quit)
	{
		frameTime = SDL_GetTicks();			//set time for beginning current frame
		tileX = 0, tileY = 0;				//reseting an destination
		actualAction = keyAction::none;		//reseting action information
		//when the music is not played
		if (Mix_PlayingMusic() == 0)
		{
			//check the end of stubborntunism instinct
			if (sm.isStubborntunismActive()) { sm.setStubborntunismActive(false); tm.setPowerupStatus(PowerupStatus::used, windowRenderer); }
			am.playMusic(AudioMusType::music);
		}

		//when the event is performed
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
				//app closing
			case SDL_QUIT: { quit = true; break; }
						 //key pressing
			case SDL_KEYDOWN:
			{
				//if character is not confused (blocked ability to move), read a key and save information about action and destination
				if (!sm.getStefan().getConfusion()) { actualAction = sterman.keyboardMovement(tileX, tileY, event.key.keysym.sym); }
				//if character gained a destination and has a little break (pause) before next step
				if (sm.getStefan().getWalkBreak()) { tileX = 0; tileY = 0; }
				break;
			}
			default: { break; }
			}
		}

		//if all treasures are found, start an winning sequence => win condition
		if (tm.getFramesLeft() == 0 && winRewardStage == 0) { winRewardStage = 1; SDL_Delay(400); }
		//if motivation is less then 0 and all treasures are not found => lose condition
		if (sm.getStefan().getMotivation() <= 0) { isLost = true; }

		//prevent performing action after level winning/losing
		if (winRewardStage == 0 && !isLost)
		{
			//move main character
			sm.moveStefan(tileX, tileY);
			//if last action is set for digging (uncovering a tile)
			if (actualAction == keyAction::digging) { digTile(); }
			//if last action is using a powerup
			else if (actualAction == keyAction::powerupUsing && tm.getPowerupStatus() == PowerupStatus::avaiable)
			{
				//for specific type of powerup, perform a proper action
				switch (tm.getPowerupType())
				{
				case treasureType::dignine: { digTile(true); break; }
				case treasureType::nosescan: { tm.showRandomTile(windowRenderer); am.playEffect(AudioEffType::nosescan, -1); SDL_Delay(500); break; }
				case treasureType::stubborntunism: { sm.setStubborntunismActive(); am.playMusic(AudioMusType::stubborntunismTheme, 0); break; }
				default: { break; }
				}
			}
		}


		//if win or lose condition is true
		if (winRewardStage > 0 || isLost)
		{
			bool goToNextLevel = false;		//flag for generating new level, can be set to true after whole sequence handling a certain condition
			am.stopMusic();					//stops actual music

			//win condition case
			switch (winRewardStage)
			{
				//does nothing (in case of unexpected condition handling)
			case 0: default: { winRewardStage = 0; break; }
				  //increment level counter and set new level flag to true (ready for generating next level)
			case 5: { level++; goToNextLevel = true; break; }
				  //increase score depending of movitation left
			case 4:
			{
				//if motivation left is bigger than 3, add some score and reduce motivation (score granting)
				if (sm.getStefan().getMotivation() > 3)
				{
					score.addScore(10);
					sm.reduceMotivation(4);
					am.playEffect(AudioEffType::pointGaining, -1);
				}
				//otherwise go to the next step of sequence
				else { sm.reduceMotivation(sm.getStefan().getMotivation()); winRewardStage++; }
				SDL_Delay(400);			//short pause
				break;
			}
			//increase score depending of uncovering or not using a powerup and take a little break
			case 3:
			{
				if (tm.getPowerupStatus() == PowerupStatus::avaiable) { score.addScore(50); }
				am.playEffect(AudioEffType::pointGaining, -1);
				winRewardStage++;
				SDL_Delay(600);
				break;
			}
			//increase score depending of finished level, go to the next step of sequence and take a little break
			case 2: { score.addScore(10 * level); am.playEffect(AudioEffType::pointGaining, -1); winRewardStage++; SDL_Delay(400); break; }
				  //increase score depending of finished level, go to the next step of sequence and take a little break
			case 1:
			{
				am.stopMusic();
				am.playMusic(AudioMusType::levelup, 0);
				SDL_Delay(2500);
				score.addScore(100);
				am.playEffect(AudioEffType::pointGaining, -1);
				winRewardStage++;
				SDL_Delay(600);
				break;
			}
			}
			//if lose condition case is fulfilled
			if (winRewardStage <= 0 && isLost)
			{
				//if best score was beaten in this (previous) game
				if (score.getScore() == bestScore.getScore()) { dati.save(level, score.getScore(), foundSnacks); }
				am.stopMusic();
				am.playMusic(AudioMusType::gameover, 0);
				SDL_Delay(2500);
				level = 1;					//reset a level counter to 1
				foundSnacks = 0;			//reset a snacks counter to 0
				score.resetScore();			//reset score to 0
				goToNextLevel = true;		//set new level flag to true (can be now generated)
			}
			//if win or lose condition sequence is completed
			if (goToNextLevel)
			{
				SDL_Delay(2000);			//take a break
				gameInit();					//load a map again
			}

		}

		//if the win (level completed) condition is not fulfilled, change the mood portrait (preventing changing it after winning)
		if (winRewardStage == 0) { lm.refreshMood(sm.getMotivationPercent(), windowRenderer); }
		//update text for left motivation and actual score
		txtm.update(std::to_string(sm.getStefan().getMotivation()), 2, font, windowRenderer);
		txtm.update(std::to_string(score.getScore()), 9, font, windowRenderer);
		if (score.getScore() > bestScore.getScore())
		{
			bestScore.addScore(score.getScore() - bestScore.getScore());
			txtm.update(std::to_string(bestScore.getScore()), 10, font, windowRenderer);
		}

		SDL_RenderClear(windowRenderer);		//clear all previous renedered objects

		txtm.render(windowRenderer);			//render all text graphs
		lm.render(0, 0, 0, windowRenderer);		//render all UI graphs
		tm.render(windowRenderer);				//render all treasure graphs
		lm.render(0, 0, 1, windowRenderer);		//render all covering tile graphs
		tm.renderIndicator(windowRenderer);		//render only indicator for nosescan ability
		sm.render(windowRenderer);				//render main character

		//if one of special action is performed last tile
		if (actualAction == keyAction::mischievous || actualAction == keyAction::anotherEvil || actualAction == keyAction::steeringHelp)
		{
			bool loop = true;					//flag for showing a life of loop, can be set to false when the app is closed
			SDL_Event event;					//sdl event variable for observing keyboard action or game exiting
			if (actualAction == keyAction::anotherEvil) { am.stopMusic(); am.playMusic(AudioMusType::menuPreTheme, 0); }

			//do unless loop is true
			while (loop)
			{
				//when the event is performed
				while (SDL_PollEvent(&event) != 0)
				{
					//app quiting or any button pressing
					switch (event.type)
					{
					case SDL_QUIT: case SDL_KEYDOWN: { loop = false; break; }
					}
				}
				//render some object depending of special action type
				switch (actualAction)
				{
				case keyAction::mischievous: { lm.render(-1, windowRenderer); break; }
				case keyAction::anotherEvil: { lm.render(-2, windowRenderer); break; }
				case keyAction::steeringHelp: { lm.render(-3, windowRenderer); break; }
				default: { break; }
				}
				SDL_RenderPresent(windowRenderer);			//window updating
			}

		}

		SDL_RenderPresent(windowRenderer);					//window updating

		//if current frame time is less than 1000/16.7 ms, wait the time difference (to have more stable 60 FPS)
		if ((SDL_GetTicks() - frameTime) < (1000.f / FPS)) { SDL_Delay((1000.f / FPS) - (SDL_GetTicks() - frameTime)); }
	}

	return true;
}

//initialazing manager base values
void GameInstance::gameInit()
{
	//layer manager reseting and generating again whole scene (UI and map elements)
	lm.exterminate();
	lm.addLayer(0, windowRenderer);
	lm.addLayer(1, windowRenderer);

	//treasure manager reseting and append new treasures on the map
	tm.exterminate();
	tm.randomizeTreasures(windowRenderer);

	//Stefan (character) manager reseting and loading again a texture with new motivation value
	sm.exterminate();
	sm.setStefan(windowRenderer);
	sm.setMotivation(99 - (level > 35 ? 70 : 2 * level) + 7 * tm.getCount() + tm.getMotivationCompensation());

	//load maximum score
	int bScore = 0;
	dati.load(bScore);
	bestScore.addScore(bScore - bestScore.getScore());

	//text manager reseting (font and text)
	txtm.exterminate();
	txtm.initalize(font, windowRenderer);
	txtm.update(std::to_string(level), 8, font, windowRenderer);
	txtm.update(std::to_string(sm.getStefan().getMotivation()), 2, font, windowRenderer);
	txtm.update(std::to_string(bestScore.getScore()), 10, font, windowRenderer);

	//audio manager
	sm.appendAudioManager(&am);

	//reseting win and lose condition variables
	isLost = false;
	winRewardStage = 0;
}

void GameInstance::digTile(bool isDignine)
{
	int initW = 0, initH = 0, endW = 1, endH = 1;						//default values for ordinary digging (only one tile)
	bool dug = false;													//flag for showing a successful digging
	//if is used dignine, set to dig nine tiles (currently standing on and the nearest)
	if (isDignine) { initW = -1; initH = -1; endW = 2; endH = 2; }
	for (initW; initW < endW; initW++)
	{
		for (int iterH = initH; iterH < endH; iterH++)
		{
			//flag is true when the tile is covered (and reveal it), unless flag is false
			dug = lm.disableTile(sm.getStefan().X() + 32 * initW, sm.getStefan().Y() + 32 * iterH);
			//if tile has been covered reduce an motivation (or not used dignine/stubborntunism)
			if (dug && !isDignine && !sm.isStubborntunismActive()) { sm.reduceMotivation(); }
			int prevTreasureCount = tm.getTreasuresLeft();				//check number of treasure to find
			//if tile containing a treasure
			if (tm.checkTile(sm.getStefan().X() + 32 * initW, sm.getStefan().Y() + 32 * iterH))
			{
				//if this tile was last uncovered tile with treasure, recover some motivation and increase snacks counter
				if (tm.getTreasuresLeft() - prevTreasureCount != 0)
				{
					sm.reduceMotivation(-10);
					foundSnacks++;
				}
				//if powerup was now discovered quickly change its status to avaiable
				if (tm.getPowerupStatus() == PowerupStatus::discovered) { tm.setPowerupStatus(PowerupStatus::avaiable, windowRenderer); }
				score.addScore(tm.returnGatheredScore());				//add gathered score during this dig action
			}
		}
	}
	//if is used dignine, change power-up status to used and play sound effect (for dignine) with little break
	if (isDignine) { tm.setPowerupStatus(PowerupStatus::used, windowRenderer); am.playEffect(AudioEffType::dignineNone, -1); SDL_Delay(100); }
	//otherwise just play sound effect (for ordinary digging) with little break
	else if (dug) { am.playEffect(AudioEffType::digNone, -1); SDL_Delay(100); }
}