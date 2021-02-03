#pragma once

#include "Graph.h"

class Stefan : public Graph
{
public:
	Stefan();
	Stefan(int x, int y);
	Stefan(int x, int y, int motivation);
	virtual ~Stefan();

	void setConfusion(bool value);
	void setMotivation(int value);
	void setWalkBreak(bool value);

	bool getConfusion();
	int getMotivation();
	bool getWalkBreak();
private:
	int motivation;
	bool confuseEffect, walkBreak;
};
