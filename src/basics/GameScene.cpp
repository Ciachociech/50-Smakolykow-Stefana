#include "..\..\include\basics\GameScene.h"

GameScene::GameScene() : actualAction(keyAction::none) {}

GameScene::~GameScene() { close(); }

void GameScene::loadRenderer(SDL_Renderer* rend) { this->windowRenderer = rend; }

void GameScene::loadFont(TTF_Font* font) { this->font = font; }

void GameScene::loadSteering(SteeringManager* sm) { this->sterman = sm; }

void GameScene::loadTexting(TextManager* tm) { this->txtm = tm; }

void GameScene::loadDating(DatInterpreter* dati) { this->dati = dati; }

void GameScene::loadAudio(AudioManager* am) { this->am = am; }

void GameScene::loadScores(ScoreManager* sm) { this->scorman = sm; }

int GameScene::loop()
{						
	SDL_Event event;							//sdl event variable for observing keyboard action or game exiting

	int tileX = 0, tileY = 0;					//movement destination of player (Stefan) counted as tile width/height (x32 coord), reseting an destination
	actualAction = keyAction::none;				//reseting action information
	//when the music is not played
	if (Mix_PlayingMusic() == 0)
	{
		//check the end of stubborntunism instinct
		if (sm.isStubborntunismActive()) { sm.setStubborntunismActive(false); tm.setPowerupStatus(PowerupStatus::used, windowRenderer); }
		am->playMusic(AudioMusType::music);
	}

	//when the event is performed
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		//app closing
		case SDL_QUIT: { return -2; break; }
		//key pressing
		case SDL_KEYDOWN:
		{
			//if character is not confused (blocked ability to move), read a key and save information about action and destination
			if (!sm.getStefan().getConfusion()) { actualAction = sterman->keyboardMovement(tileX, tileY, event.key.keysym.sym); }
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
			case treasureType::nosescan: { tm.showRandomTile(windowRenderer); am->playEffect(AudioEffType::nosescan, -1); SDL_Delay(500); break; }
			case treasureType::stubborntunism: { sm.setStubborntunismActive(); am->playMusic(AudioMusType::stubborntunismTheme, 0); break; }
			default: { break; }
			}
		}
	}

	//if win or lose condition is true
	if (winRewardStage > 0 || isLost)
	{
		bool goToNextLevel = false;		//flag for generating new level, can be set to true after whole sequence handling a certain condition
		am->stopMusic();					//stops actual music

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
				scorman->getActualScore().addScore(10);
				sm.reduceMotivation(4);
				am->playEffect(AudioEffType::pointGaining, -1);
			}
			//otherwise go to the next step of sequence
			else { sm.reduceMotivation(sm.getStefan().getMotivation()); winRewardStage++; }
			SDL_Delay(400);			//short pause
			break;
		}
		//increase score depending of uncovering or not using a powerup and take a little break
		case 3:
		{
			if (tm.getPowerupStatus() == PowerupStatus::avaiable) { scorman->getActualScore().addScore(50); }
			am->playEffect(AudioEffType::pointGaining, -1);
			winRewardStage++;
			SDL_Delay(600);
			break;
		}
		//increase score depending of finished level, go to the next step of sequence and take a little break
		case 2: 
		{ 
			scorman->getActualScore().addScore(10 * level); 
			am->playEffect(AudioEffType::pointGaining, -1); 
			winRewardStage++; 
			SDL_Delay(400); 
			break; 
		}
		//increase score depending of finished level, go to the next step of sequence and take a little break
		case 1:
		{
			am->stopMusic();
			am->playMusic(AudioMusType::levelup, 0);
			SDL_Delay(2500);
			scorman->getActualScore().addScore(100);
			am->playEffect(AudioEffType::pointGaining, -1);
			winRewardStage++;
			SDL_Delay(600);
			break;
		}
		}
		//if lose condition case is fulfilled
		if (winRewardStage <= 0 && isLost)
		{
			//if best score was beaten in this (previous) game or size of score table is quite short
			if (scorman->getActualScore().getScore() == scorman->getBestScore().getScore() || scorman->getSize() < 5) 
			{ 
				dati->save(scorman->saveActualScore(level, foundSnacks)); 
			}
			am->stopMusic();
			am->playMusic(AudioMusType::gameover, 0);
			SDL_Delay(2500);
			level = 1;										//reset a level counter to 1
			foundSnacks = 0;								//reset a snacks counter to 0
			scorman->getActualScore().resetScore();			//reset score to 0
			goToNextLevel = true;							//set new level flag to true (can be now generated)
		}
		//if win or lose condition sequence is completed
		if (goToNextLevel)
		{
			SDL_Delay(2000);								//take a break
			init();											//load a map again
		}

	}

	//if the win (level completed) condition is not fulfilled, change the mood portrait (preventing changing it after winning)
	if (winRewardStage == 0) { lm.refreshMood(sm.getMotivationPercent(), windowRenderer); }
	//update text for left motivation and actual score
	txtm->update(textType::scene, std::to_string(sm.getStefan().getMotivation()), 2, font, windowRenderer);
	txtm->update(textType::scene, std::to_string(scorman->getActualScore().getScore()), 9, font, windowRenderer);
	if (scorman->getActualScore().getScore() > scorman->getBestScore().getScore())
	{
		txtm->update(textType::scene, std::to_string(scorman->getActualScore().getScore()), 10, font, windowRenderer);
	}

	if (actualAction != keyAction::pause) { return 0; }
	else { return -1; }
}

void GameScene::init()
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
	dati->load(*scorman);

	//text manager reseting (font and text)
	txtm->exterminate(textType::scene);
	txtm->initalize(textType::scene, font, windowRenderer);
	txtm->update(textType::scene, std::to_string(level), 8, font, windowRenderer);
	txtm->update(textType::scene, std::to_string(sm.getStefan().getMotivation()), 2, font, windowRenderer);
	txtm->update(textType::scene, std::to_string(scorman->getBestScore().getScore()), 10, font, windowRenderer);

	//audio manager
	sm.appendAudioManager(am);

	//reseting win and lose condition variables
	isLost = false;
	winRewardStage = 0;
}

void GameScene::close()
{
	font = NULL;
	sterman = NULL;
	txtm = NULL;
	dati = NULL;
	am = NULL;
	scorman = NULL;
}

void GameScene::render()
{
	renderPanel();
	renderScene();
	//if one of special action is performed last tile
	if (actualAction == keyAction::mischievous || actualAction == keyAction::anotherEvil || actualAction == keyAction::steeringHelp)
	{
		bool loop = true;												//flag for showing a life of loop, can be set to false when the app is closed
		SDL_Event event;												//sdl event variable for observing keyboard action or game exiting
		if (actualAction == keyAction::anotherEvil) { am->stopMusic(); am->playMusic(AudioMusType::menuPreTheme, 0); }

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
			SDL_RenderPresent(windowRenderer);							//window updating
		}

	}
}

void GameScene::renderScene()
{
	lm.render(0, 0, -4, windowRenderer);								//render logo graph
	lm.render(0, 0, 0, windowRenderer);									//render all UI graphs
	tm.renderScene(windowRenderer);										//render only indicator for nosescan ability
	lm.render(0, 0, 1, windowRenderer);									//render all covering tile graphs
	sm.render(windowRenderer);											//render main character
	tm.renderIndicator(windowRenderer);									//render nosescan indicator
}

void GameScene::renderPanel()
{
	lm.render(0, 0, -5, windowRenderer);								//render mood tile graph
	txtm->render(textType::scene, windowRenderer);						//render all text graphs
	tm.renderPanel(windowRenderer);										//render all treasure graphs
}

void GameScene::digTile(bool isDignine)
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
				scorman->getActualScore().addScore(tm.returnGatheredScore());				//add gathered score during this dig action
			}
		}
	}
	//if is used dignine, change power-up status to used and play sound effect (for dignine) with little break
	if (isDignine) { tm.setPowerupStatus(PowerupStatus::used, windowRenderer); am->playEffect(AudioEffType::dignineNone, -1); SDL_Delay(100); }
	//otherwise just play sound effect (for ordinary digging) with little break
	else if (dug) { am->playEffect(AudioEffType::digNone, -1); SDL_Delay(100); }
}
