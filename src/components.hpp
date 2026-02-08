#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SDL.h>

struct Position {
    float x;
    float y;
};

struct Size {
    int width;
    int height;

};

// struct Color; это SDL_Color!

struct Sprite {
    int index;
    SDL_Rect src;
    int width;
    int height;
};

struct Collide {
    float x;
    float y;
    int width;
    int height;
};

#endif