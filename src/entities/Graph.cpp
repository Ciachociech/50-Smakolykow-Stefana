#include "..\..\include\entities\Graph.h"

Graph::Graph() : x(0), y(0), w(0), h(0), frames(1), sides(1), currentFrame(0), scaleX(1.f), scaleY(1.f),texture(NULL), spriteSide(lookAt::left) {}

Graph::Graph(int x, int y) : x(x), y(y), w(0), h(0), frames(1), sides(1), currentFrame(0), scaleX(1.f), scaleY(1.f), texture(NULL), spriteSide(lookAt::left) {}

Graph::~Graph() {}

//loads a texture from file with scale and without animation
bool Graph::loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	free();													//erase all previous information about texture

	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(filepath.c_str());		//load image from certain file
	//if image is not loaded
	if (surface == NULL) { printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
	//otherwise, try to make texture
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		//if texture cannot be made
		if (texture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
		//otherwise set variables describing an image
		else
		{
			this->w = surface->w;
			this->h = surface->h;
			this->scaleX = scaleX;
			this->scaleY = scaleY;
			this->frames = 1;
		}

		SDL_FreeSurface(surface);							//free surface
	}

	firstInit = false;										//set initialization flag for false
	this->texture = texture;								//append new created texture to object variable
	return this->texture != NULL;							//return result of appending
}

//loads a texture from file with scale and animation
bool Graph::loadFromFile(float scaleX, float scaleY, int frames, int sides, std::string filepath, SDL_Renderer* renderer)
{
	free();													//erase all previous information about texture

	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(filepath.c_str());		//load image from certain file
	//if image is not loaded
	if (surface == NULL) { printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
	//otherwise set variables describing an image
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		//if texture cannot be made
		if (texture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
		//otherwise set variables describing an image
		else
		{
			this->w = surface->w / frames;
			this->h = surface->h / sides;
			this->scaleX = scaleX;
			this->scaleY = scaleY;
			this->frames = frames;
			this->sides = sides;
		}

		SDL_FreeSurface(surface);							//free surface
	}

	firstInit = false;										//set initialization flag for false
	this->texture = texture;								//append new created texture to object variable
	return this->texture != NULL;							//return result of appending
}

//loads a texture from text (string, color and aligning) - suggested for left alignment
bool Graph::loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, bool isLeftside)
{
	free();																					//erase all previous information about texture

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//load image from text (font, string and color)
	//if image is not loaded
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	//otherwise, try to make texture
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//if texture cannot be made
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		//otherwise set variables describing an image
		else
		{
			this->w = textSurface->w / frames;
			this->h = textSurface->h;
			if (!isLeftside && firstInit) { x -= this->w; }									//if align is right, set the x coord of alignment
		}

		SDL_FreeSurface(textSurface);														//free surface
	}

	firstInit = false;																		//set initialization flag for false
	return texture != NULL;																	//return result of appending
}

//loads a texture from text (string, color and aligning) - suggested for right alignment
bool Graph::loadFromText(int alignX, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, bool isLeftside)
{
	free();																					//erase all previous information about texture

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//load image from text (font, string and color)
	//if image is not loaded
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	//otherwise, try to make texture
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//if texture cannot be made
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		//otherwise set variables describing an image
		else
		{
			this->w = textSurface->w / frames;
			this->h = textSurface->h;
			if (!isLeftside) { this->x = alignX - this->w; }
		}

		SDL_FreeSurface(textSurface);														//free surface
	}

	firstInit = false;																		//set initialization flag for false
	return texture != NULL;																	//return result of appending
}

//reseting texture and information about it
void Graph::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		w = 0;
		h = 0;
	}
}

//render texture with certain coords (camera position)
void Graph::render(int x, int y, SDL_Renderer* renderer)
{
	if (frames > 1) { ++currentFrame; }																				//invoke next animation frame
	SDL_Rect srcRenderQuad = { ((currentFrame + 1) / (30 / frames)) % frames * w, (int) (spriteSide) * h, w, h };	//texture to render (from file)
	SDL_Rect dstRenderQuad = { this->x + x, this->y + y, scaleX * w, scaleY * h };									//place to render texture (on scene)
	SDL_RenderCopy(renderer, texture, &srcRenderQuad, &dstRenderQuad);												//SDL rendering function
}

//render texture with texture coords
void Graph::render(SDL_Renderer* renderer)
{
	if (frames > 1) { ++currentFrame; }																				//invoke next animation frame
	SDL_Rect srcRenderQuad = { ((currentFrame + 1) / (30 / frames)) % frames * w, (int)(spriteSide) * h, w, h };	//texture to render (from file)
	SDL_Rect dstRenderQuad = { this->x, this->y, scaleX * w, scaleY * h };											//place to render texture (on scene)
	SDL_RenderCopy(renderer, texture, &srcRenderQuad, &dstRenderQuad);												//SDL rendering function
}

//returning position coord (x, y) and dimension (w, h)
int Graph::X() { return this->x; }

int Graph::Y() { return this->y; }

int Graph::W() { return this->w; }

int Graph::H() { return this->h; }

//set new position
void Graph::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

//set new side of texture
void Graph::setSpriteSide(lookAt newSide) { spriteSide = newSide; }
