#pragma once

#include "external_dependencies.h"

enum class lookAt { none = -1, left = 0, right, up, down};

class Graph
{
public:
	Graph();
	Graph(int x, int y);
	virtual ~Graph();

	virtual bool loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer);
	virtual bool loadFromFile(float scaleX, float scaleY, int frames, int sides, std::string filepath, SDL_Renderer* renderer);
	bool loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, bool isLeftside);
	bool loadFromText(int alignX, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, bool isLeftside);
	void free();
	virtual void render(int x, int y, SDL_Renderer* renderer);
	virtual void render(SDL_Renderer* renderer);

	int X();
	int Y();
	int W();
	int H();

	void setXY(int x, int y);
	void setSpriteSide(lookAt newSide);
private:
	SDL_Texture* texture;
	
	int x, y;
	int w, h;
	float scaleX, scaleY;
	int frames, sides, currentFrame = 0;
	bool firstInit = true;
	lookAt spriteSide;
};

typedef std::vector<std::unique_ptr<Graph>> VecGraph;