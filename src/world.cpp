#include "world.hpp"

World::World() {
    nextId = 0;
}

void World::reserve(int number) {
    number++;
    positions.resize(number);
    sizes.resize(number);
    colors.resize(number);
    sprites.resize(number);
    colliders.resize(number);

    hasPositions.assign(number, false);
    hasSizes.assign(number, false);
    hasColors.assign(number, false);
    hasSprites.assign(number, false);
    hasColliders.assign(number, false);

    flags.assign(number, 0);
}

int World::capycity() { return flags.size(); }

int World::createEntity() {
    if (nextId >= flags.size()) return -1; else return nextId++;
}

void World::deleteEntity(int id) {
    hasPositions[id] = false;
    hasSizes[id] = false;
    hasColors[id] = false;
    hasSprites[id] = false;
    hasColliders[id] = false;
}


void World::addComponent(int id, Position pos) {
    positions[id] = pos;
    hasPositions[id] = true;
}

void World::addComponent(int id, Size size) {
    sizes[id] = size;
    hasSizes[id] = true;
}

void World::addComponent(int id, SDL_Color color) {
    colors[id] = color;
    hasColors[id] = true;
}

void World::addComponent(int id, Sprite sprite) {
    sprites[id] = sprite;
    hasSprites[id] = true;
}

void World::addComponent(int id, Collide collider) {
    colliders[id] = collider;
    hasColliders[id] = true;
}


// геты

Position& World::getPosition(int id) {
    return positions[id];
}

Size& World::getSize(int id) {
    return sizes[id];
}

SDL_Color& World::getColor(int id) {
    return colors[id];
}

Sprite& World::getSprite(int id) {
    return sprites[id];
}

Collide& World::getCollide(int id) {
    return colliders[id];
}

// сеты
void World::setFlags(int id, unsigned int value) {
    flags[id] = value;
}

// хасы
bool World::hasFlag(int id, unsigned int mask) {
    return (flags[id] & mask);
}