#pragma once

#include "Score.h"

class HistoryScore : public Score
{
private:
	int gainedLevel;
	int collectedTidbits;
	std::string nickname;
	std::string date;
	std::string version;
public:
	HistoryScore();
	HistoryScore(int value);
	virtual ~HistoryScore();

	int getGainedLevel();
	int getCollectedTidbits();
	std::string getNickname();
	std::string getDate();
	std::string getVersion();

	void setGainedLevel(int level);
	void setCollectedTidbits(int tidbits);
	void setNickname(std::string nickname);
	void setDate(std::string date);
	void setVersion(std::string version);
};

