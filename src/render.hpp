#ifndef RENDER_HPP
#define RENDER_HPP

#include <SDL.h>

#include "context.hpp"

enum RenderType { TYPE_SPRITE, TYPE_RECT };

struct RenderItem {
	int x;
	int y;
	int width;
	int height;
	SDL_Color color;
	int index;
	SDL_Rect tile;
	RenderType type;
};

class Render {
private:
	std::vector<SDL_Texture*> textures;
	std::vector<RenderItem> sprites;

public:
	~Render();

	int getTexture(SDL_Texture* texture);

	void drawRect(int x, int y, int width, int height, SDL_Color color);

	void drawSprite(int x, int y, int width, int height, SDL_Color color, int index, SDL_Rect tile);
	
	void render();
	
};

#endif