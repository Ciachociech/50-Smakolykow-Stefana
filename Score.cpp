#include "Score.h"

Score::Score() : value(0) {}

Score::Score(int value) : value(value) {}

Score::~Score() {}

int Score::getScore() { return this->value; }

std::string Score::txtScore() { return std::to_string(this->value); }

void Score::addScore(int addValue) { this->value += addValue; }

void Score::resetScore() { this->value = 0; }
