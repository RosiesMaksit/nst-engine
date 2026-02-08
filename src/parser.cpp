#include "parser.hpp"
#include "components.hpp"
#include <iostream>

int Parser::loadNST(const std::string& path, World& world) {

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "FILE NOT FOUND!" << std::endl;
        return -1;
    }

    unsigned char nst[3];
    file.read((char*)nst, 3);

    if (!(nst[0] == 'N' && nst[1] == 'S' && nst[2] == 'T')) {
        return -1;
    }

    unsigned char b2[2];
    unsigned char b4[4];

    file.read((char*)b2, 2);
    int count = (b2[0] << 8) | b2[1]; // Фиксированный порядок

    world.reserve(99);

    SDL_Color background;
    file.read((char*)&background, 4);

    file.seekg(32, std::ios::beg);

    unsigned char buffer;
    unsigned char components;

    int entity;

    for (int i = 0; i < count; i++) {

        entity = world.createEntity();

        float x = 0, y = 0;
        unsigned short width = 0, height = 0;
        unsigned char r = 255, g = 255, b = 255, a = 255;

        int index = 0, srcx = 0, srcy = 0, srcw = 0, srch = 0, swidth = 0, sheight = 0;
        float cx = 0, cy = 0;
        int cwidth = 0, cheight = 0;

        file.read((char*)&components, 1);

        for (int id = 0; id < (int)components; id++) {
            file.read((char*)&buffer, 1);

            if (buffer == 0xE0) { // Position (Signed)
                file.read((char*)b4, 4);
                x = (float)((signed int)((b4[0] << 24) | (b4[1] << 16) | (b4[2] << 8) | b4[3]));
                file.read((char*)b4, 4);
                y = (float)((signed int)((b4[0] << 24) | (b4[1] << 16) | (b4[2] << 8) | b4[3]));

                world.addComponent(entity, Position{x, y});

            } else if (buffer == 0xE1) { // Size (Unsigned)
                file.read((char*)b2, 2);
                width = (unsigned short)((b2[0] << 8) | b2[1]);
                file.read((char*)b2, 2);
                height = (unsigned short)((b2[0] << 8) | b2[1]);

                world.addComponent(entity, Size{width, height});

            } else if (buffer == 0xE2) { // RGBA
                file.read((char*)&r, 1);
                file.read((char*)&g, 1);
                file.read((char*)&b, 1);
                file.read((char*)&a, 1);

                world.addComponent(entity, SDL_Color{r, g, b, a});

            } else if (buffer == 0xE3) { // Sprite
                unsigned char b1;
                file.read((char*)&b1, 1); index = (int)b1;
                
                file.read((char*)b2, 2); srcx = (int)((b2[0] << 8) | b2[1]);
                file.read((char*)b2, 2); srcy = (int)((b2[0] << 8) | b2[1]);
                
                file.read((char*)&b1, 1); srcw = (int)b1;
                file.read((char*)&b1, 1); srch = (int)b1;
                
                file.read((char*)b2, 2); swidth = (int)((b2[0] << 8) | b2[1]);
                file.read((char*)b2, 2); sheight = (int)((b2[0] << 8) | b2[1]);

                world.addComponent(entity, Sprite{index, SDL_Rect{srcx, srcy, srcw, srcy}, swidth, sheight});

            } else if (buffer == 0xE4) { // Collide
                file.read((char*)b2, 2); // cx (Signed)
                cx = (float)((signed short)((b2[0] << 8) | b2[1]));
                
                file.read((char*)b2, 2); // cy (Signed)
                cy = (float)((signed short)((b2[0] << 8) | b2[1]));
                
                file.read((char*)b2, 2); // cw (Unsigned)
                cwidth = (int)((unsigned short)((b2[0] << 8) | b2[1]));
                
                file.read((char*)b2, 2); // ch (Unsigned)
                cheight = (int)((unsigned short)((b2[0] << 8) | b2[1]));

                world.addComponent(entity, Collide{cx, cy, cwidth, cheight});
            }
        }

        file.read((char*)b4, 4);
        unsigned int f = (unsigned int)((b4[0] << 24) | (b4[1] << 16) | (b4[2] << 8) | b4[3]);
        world.setFlags(i, f);
    }

    return 0;
}