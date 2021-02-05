#pragma once

#include "external_dependencies.h"

class Score
{
public:
	Score();
	Score(int value);
	~Score();

	int getScore();
	std::string txtScore();
	void addScore(int addValue);
	void resetScore();
private:
	int value;
};

