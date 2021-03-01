#pragma once

#include "external_dependencies.h"

//enum containing information for displaying a spritesheet side (for main character)
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
	SDL_Texture* texture;						//object texture
	
	int x, y;									//object coords
	int w, h;									//object dims
	float scaleX, scaleY;						//object scale of dimes
	int frames, sides, currentFrame = 0;		//number of object frames (more than one for animation), current shown frame and sides of texture
	lookAt spriteSide;							//shows a side to show
	bool firstInit = true;						//flag for controlling initialization, after this is set to false
};

typedef std::vector<std::unique_ptr<Graph>> VecGraph;