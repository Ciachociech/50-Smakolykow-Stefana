#include "Graph.h"

Graph::Graph() : x(0), y(0), w(0), h(0), frames(1), sides(1), currentFrame(0), scaleX(1.f), scaleY(1.f),texture(NULL), spriteSide(lookAt::left) {}

Graph::Graph(int x, int y) : x(x), y(y), w(0), h(0), frames(1), sides(1), currentFrame(0), scaleX(1.f), scaleY(1.f), texture(NULL), spriteSide(lookAt::left) {}

Graph::~Graph() {}

bool Graph::loadFromFile(float scaleX, float scaleY, std::string filepath, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface == NULL) { printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
		else
		{
			this->w = surface->w;
			this->h = surface->h;
			this->scaleX = scaleX;
			this->scaleY = scaleY;
			this->frames = 1;
		}

		SDL_FreeSurface(surface);
	}

	firstInit = false;
	this->texture = texture;
	return this->texture != NULL;
}

bool Graph::loadFromFile(float scaleX, float scaleY, int frames, int sides, std::string filepath, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface == NULL) { printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError()); }
		else
		{
			this->w = surface->w / frames;
			this->h = surface->h / sides;
			this->scaleX = scaleX;
			this->scaleY = scaleY;
			this->frames = frames;
			this->sides = sides;
		}

		SDL_FreeSurface(surface);
	}

	firstInit = false;
	this->texture = texture;
	return this->texture != NULL;
}

bool Graph::loadFromText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font, bool isLeftside)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			this->w = textSurface->w / frames;
			this->h = textSurface->h;
			if (!isLeftside && firstInit) { x -= this->w; }
		}

		SDL_FreeSurface(textSurface);
	}

	firstInit = false;
	return texture != NULL;
}

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

void Graph::render(int x, int y, SDL_Renderer* renderer)
{
	if (frames > 1) { ++currentFrame; }
	SDL_Rect srcRenderQuad = { ((currentFrame + 1) / (30 / frames)) % frames * w, (int) (spriteSide) * h, w, h };
	SDL_Rect dstRenderQuad = { this->x + x, this->y + y, scaleX * w, scaleY * h };
	SDL_RenderCopy(renderer, texture, &srcRenderQuad, &dstRenderQuad);
}

void Graph::render(SDL_Renderer* renderer)
{
	if (frames > 1) { ++currentFrame; }
	SDL_Rect srcRenderQuad = { ((currentFrame + 1) / (30 / frames)) % frames * w, (int)(spriteSide) * h, w, h };
	SDL_Rect dstRenderQuad = { this->x, this->y, scaleX * w, scaleY * h };
	SDL_RenderCopy(renderer, texture, &srcRenderQuad, &dstRenderQuad);
}

int Graph::X() { return this->x; }

int Graph::Y() { return this->y; }

void Graph::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Graph::setSpriteSide(lookAt newSide) { spriteSide = newSide; }
