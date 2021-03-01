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
	void setWalkBreak(bool value);
	void setMotivation(int value);
	void setBaseMotivation(int value);

	bool getConfusion();
	bool getWalkBreak();
	int getMotivation();
	int getBaseMotivation();
private:
	int motivation, baseMotivation;			//current and base motivation for main character
	bool confuseEffect, walkBreak;			//flags for movement preventing (after hitting a wall or gaining a destination)
};

