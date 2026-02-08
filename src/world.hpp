#ifndef WORLD_HPP
#define WORLD_HPP

#include "components.hpp"
#include <vector>

class World {
private:
    std::vector<Position> positions;
    std::vector<Size> sizes;
    std::vector<SDL_Color> colors;
    std::vector<Sprite> sprites;
    std::vector<Collide> colliders;
    std::vector<unsigned int> flags;

    int nextId;

public:

    std::vector<bool> hasPositions;
    std::vector<bool> hasSizes;
    std::vector<bool> hasColors;
    std::vector<bool> hasSprites;
    std::vector<bool> hasColliders;

    World();

    void reserve(int number);
    int capycity();
    int createEntity();
    void deleteEntity(int id);

    // адды
    void addComponent(int id, Position pos);
    void addComponent(int id, Size size);
    void addComponent(int id, SDL_Color color);
    void addComponent(int id, Sprite sprite);
    void addComponent(int id, Collide collide);

    // геты
    Position& getPosition(int id);
    Size& getSize(int id);
    SDL_Color& getColor(int id);
    Sprite& getSprite(int id);
    Collide& getCollide(int id);

    // сеты
    void setFlags(int id, unsigned int value);


    // хасы
    bool hasFlag(int id, unsigned int mask);

};

#endif