#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>

#include <vector>

extern const int width;
extern const int height;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

class Render;
extern Render render;

extern bool running;

extern const Uint8* keys;

bool init();

void destroyContext();

#endif