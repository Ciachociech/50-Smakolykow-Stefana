#include "..\..\include\basics\Score.h"

Score::Score() : value(0) {}

Score::Score(int value) : value(value) {}

Score::~Score() {}

int Score::getScore() { return this->value; }

//Returns score as a string
std::string Score::txtScore() { return std::to_string(this->value); }

//Add a value to current score
void Score::addScore(int addValue) { this->value += addValue; }

//Reset actual score
void Score::resetScore() { this->value = 0; }
