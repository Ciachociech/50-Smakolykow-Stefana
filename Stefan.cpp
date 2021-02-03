#include "Stefan.h"

Stefan::Stefan() : Graph(), motivation(-1), confuseEffect(false), walkBreak(false) {}

Stefan::Stefan(int x, int y) : Graph(x, y), motivation(-1), confuseEffect(false), walkBreak(false) {}

Stefan::Stefan(int x, int y, int motivation) : Graph(x,y), motivation(motivation), confuseEffect(false), walkBreak(false) {}

Stefan::~Stefan() { Graph::~Graph(); }

void Stefan::setConfusion(bool value) { this->confuseEffect = value; }

void Stefan::setMotivation(int value) { this->motivation = value; }

void Stefan::setWalkBreak(bool value) { this->walkBreak = value; }

bool Stefan::getConfusion() { return confuseEffect; }

int Stefan::getMotivation() { return motivation; }

bool Stefan::getWalkBreak() { return walkBreak; }