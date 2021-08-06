#include "..\..\include\basics\HistoryScore.h"

HistoryScore::HistoryScore() : Score(0), gainedLevel(0), collectedTidbits(0), date("2021/8/4"), version("0.9.9") {}

HistoryScore::HistoryScore(int value) : Score(value), gainedLevel(0), collectedTidbits(0), date("2021/8/4"), version("0.9.9") {}

HistoryScore::~HistoryScore() {}

int HistoryScore::getGainedLevel() { return gainedLevel; }

int HistoryScore::getCollectedTidbits() { return collectedTidbits; }

std::string HistoryScore::getDate() { return date; }

std::string HistoryScore::getVersion() { return version; }

void HistoryScore::setGainedLevel(int level) { this->gainedLevel = level; }

void HistoryScore::setCollectedTidbits(int tidbits) { this->collectedTidbits = tidbits; }

void HistoryScore::setDate(std::string date) { this->date = date; }

void HistoryScore::setVersion(std::string version) { this->version = version; }
