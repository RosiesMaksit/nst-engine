#include "context.hpp"


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

const int width = 800;
const int height = 600;

bool running = true;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }
	if (TTF_Init() == -1) {
		SDL_Quit();
		return false;
	}
	
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		SDL_Quit();
		TTF_Quit();
		return false;
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		return false;
		
	}
	
	
	window = SDL_CreateWindow("Window :)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	
    if (!window) {
        SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
        return false;
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
        return false;
    }
	
	return true;

}

void destroyContext() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}