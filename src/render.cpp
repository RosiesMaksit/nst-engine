#include "render.hpp"
#include <algorithm>

Render render;

Render::~Render() {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();
}

int Render::getTexture(SDL_Texture* texture) {
	textures.push_back(texture);
	
	return textures.size() - 1;
}

void Render::drawRect(int x, int y, int width, int height, SDL_Color color) {
    RenderItem item = {x, y, width, height, color, -1, {0,0,0,0}, TYPE_RECT};
    sprites.push_back(item);
}

void Render::drawSprite(int x, int y, int width, int height, SDL_Color color, int index, SDL_Rect tile) {
	RenderItem sprite = {x, y, width, height, color, index, tile};
	sprites.push_back(sprite);
}

void Render::render() {
	std::stable_sort(sprites.begin(), sprites.end(), [](const RenderItem& a, const RenderItem& b) {
		return a.y + a.height < b.y + b.height;
	});
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	
    for (RenderItem& s : sprites) {
        SDL_Rect rect = {s.x, s.y, s.width, s.height};
        if (s.type == TYPE_SPRITE) {
            SDL_SetTextureColorMod(textures[s.index], s.color.r, s.color.g, s.color.b);
            SDL_SetTextureAlphaMod(textures[s.index], s.color.a);
            SDL_RenderCopy(renderer, textures[s.index], &s.tile, &rect);
        } else {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Для прозрачности
            SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g, s.color.b, s.color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
	
	SDL_RenderPresent(renderer);
	sprites.clear();
}