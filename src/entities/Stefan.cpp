#include "..\..\include\entities\Stefan.h"

Stefan::Stefan() : Graph(), motivation(-1), baseMotivation(-1), confuseEffect(false), walkBreak(false) {}

Stefan::Stefan(int x, int y) : Graph(x, y), motivation(-1), baseMotivation(-1), confuseEffect(false), walkBreak(false) {}

Stefan::Stefan(int x, int y, int motivation) : Graph(x,y), motivation(motivation), baseMotivation(motivation), confuseEffect(false), walkBreak(false) {}

Stefan::~Stefan() { Graph::~Graph(); }

//Sets certain variables (confusion status and walk break status, current and base motivation points)
void Stefan::setConfusion(bool value) { this->confuseEffect = value; }

void Stefan::setWalkBreak(bool value) { this->walkBreak = value; }

void Stefan::setMotivation(int value) { this->motivation = value; }

void Stefan::setBaseMotivation(int value) { this->baseMotivation = value; this->motivation = value; }

//Returns certain variables (confusion status and walk break status, current and base motivation points)
bool Stefan::getConfusion() { return confuseEffect; }

bool Stefan::getWalkBreak() { return walkBreak; }

int Stefan::getMotivation() { return motivation; }

int Stefan::getBaseMotivation() { return baseMotivation; }
