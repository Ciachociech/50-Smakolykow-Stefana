#include "Stefan.h"

Stefan::Stefan() : Graph(), motivation(-1), confuseEffect(false) {}

Stefan::Stefan(int x, int y) : Graph(x, y), motivation(-1), confuseEffect(false) {}

Stefan::Stefan(int x, int y, int motivation) : Graph(x,y), motivation(motivation), confuseEffect(false) {}

Stefan::~Stefan() { Graph::~Graph(); }

void Stefan::setConfusion(bool value) { confuseEffect = value; }

void Stefan::setMotivation(int value) { this->motivation = value; }

bool Stefan::getConfusion() { return confuseEffect; }

int Stefan::getMotivation() { return motivation; }
