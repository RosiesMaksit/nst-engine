#include "system.hpp"
#include "render.hpp"

void drawSystem(World& world) {
    for (int id = 0; id < world.capycity(); ++id) {
        if (!world.hasPositions[id] || !world.hasSizes[id]) continue;

        Position& pos = world.getPosition(id);
        Size& size = world.getSize(id);
        SDL_Color color = world.hasColors[id] ? world.getColor(id) : SDL_Color{255, 255, 255, 255};

        if (world.hasSprites[id]) {
            Sprite& sprite = world.getSprite(id);
            render.drawSprite(pos.x, pos.y, size.width, size.height, color, sprite.index, sprite.src);
        } else {
            render.drawRect(pos.x, pos.y, size.width, size.height, color);
        }
    }
    render.render(); // Вызываем отрисовку всего накопленного
}