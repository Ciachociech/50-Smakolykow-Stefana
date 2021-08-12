#include "..\..\include\managers\ScoreManager.h"

//select the place+1-th (default - the best) score and return it
HistoryScore ScoreManager::selectBestScore(int place)
{
	if (allScores.size() > 0 && place < allScores.size()) 
	{
		//read place+1 scores to scoreIndex vector, to be sure that last score is that we want to return
		std::vector<ScoreIndex> scoreBuffer = std::vector<ScoreIndex>();
		for (int it = 0; it <= place; it++) {
			scoreBuffer.push_back(ScoreIndex(it, allScores[it]->getScore()));
		}
		//sort and reverse scoreIndex vector (to get decreasing order) each time the vector is changed
		std::sort(scoreBuffer.begin(), scoreBuffer.end());
		std::reverse(scoreBuffer.begin(), scoreBuffer.end());

		for (int it = place + 1; it < allScores.size(); it++)
		{
			//if actual read score is bigger than last (interesting) score
			if (allScores[it]->getScore() > scoreBuffer[place].score)
			{
				scoreBuffer[place].index = it;
				scoreBuffer[place].score = allScores[it]->getScore();
				//sort and reverse again
				std::sort(scoreBuffer.begin(), scoreBuffer.end());
				std::reverse(scoreBuffer.begin(), scoreBuffer.end());
			}
		}
		//return place+1-th score
		return *allScores[scoreBuffer[place].index].get();
	}
	//if something went wrong return -1 as score, will be interesting for player see some strange values
	HistoryScore emptyScore(-1);
	emptyScore.setGainedLevel(-1);
	emptyScore.setCollectedTidbits(-1);
	emptyScore.setDate("2020/6/26");
	emptyScore.setVersion("0.9.8");
	return emptyScore;
}

ScoreManager::ScoreManager() {}

ScoreManager::~ScoreManager()
{
	exterminate();
	allScores.~vector();
}

Score& ScoreManager::getActualScore() { return actualScore; }

HistoryScore ScoreManager::getBestScore(int index) { return selectBestScore(index); }

//get size of HistoryIndex vector (number of saved scores)
int ScoreManager::getSize() { return allScores.size(); }

//get an index to shown place on scoreboard
int ScoreManager::getShownPlace() { return shownPlace; }

bool ScoreManager::incrementPlace() 
{
	if (shownPlace < 4 && shownPlace < getSize() - 1) { shownPlace++; return true; }
	return false;
}

bool ScoreManager::decrementPlace()
{
	if (shownPlace > 0) { shownPlace--; return true; }
	return false;
}

//resets index to first position in scoreboard
void ScoreManager::resetPlace() { shownPlace = 0; }

//add a history score to vector
bool ScoreManager::addHistoryScore(HistoryScore& score) 
{ 
	allScores.push_back(std::make_unique<HistoryScore>(score));
	return true; 
}

//convert actual score to history score (used before saving to .dat file) - be sure to reset actual score after calling this method
HistoryScore ScoreManager::saveActualScore(int level, int foundSnacks)
{
	HistoryScore hiscore(actualScore.getScore());
	hiscore.setGainedLevel(level);
	hiscore.setCollectedTidbits(foundSnacks);
	return hiscore;
}

//clear all written scores and clear vector
void ScoreManager::exterminate()
{
	for (auto& score : allScores) { score.reset(); }
	allScores.clear();
	resetPlace();
}