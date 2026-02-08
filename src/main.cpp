// обязательное
#define _WIN32_WINNT 0x0601
// библиотеки

// собственное
#include "context.hpp"
#include "system.hpp"
#include "parser.hpp"

// сторонние

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Инициализация SDL
	if (!init()) return -1;
    SDL_Event event;

    // переменные заранее
    Parser parser;
    
    World* current_world;
    World game;

    parser.loadNST("test.nst", game);
	
    while (running) {
        // Обработка событий (цикл)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
			// current_world->handle_input(&event);
        }
        // handle input
        keys = SDL_GetKeyboardState(NULL);
        // if (keys[SDL_SCANCODE_W]) { y -= speed; }

        drawSystem(game);

        SDL_RenderPresent(renderer);
    }

    // Очистка ресурсов
    destroyContext();

    return 0;
}