#include "SeekWorld.h"
#include "draw.h"
#include "world.h"
#include <SDL.h>
#include <cstdlib>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void main_loop(void *);

World *world = new SeekWorld();
SDL_Window *win;
SDL_Renderer *ren;
unsigned int sim_time;
bool quit = false;

int main() {
    std::cout << "start" << std::endl;

    using std::cout;
    using std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    win =
        SDL_CreateWindow("Hello World!", 100, 100, 620, 387, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cout << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    sim_time = SDL_GetTicks();

    std::cout << "preloop" << std::endl;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, NULL, 0, true);
#else
    while (!quit) {
        main_loop(nullptr);
    }
#endif
}

void main_loop(void *arg) {
    Draw draw = Draw(ren);
    draw.clear();

    world->render(draw);
    SDL_RenderPresent(ren);

    while (sim_time < SDL_GetTicks()) {
        world->step();
        sim_time += (int)world->get_step_milliseconds();
    };

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {

            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);

            world->click(x, y);
        }
    }
    int wait = sim_time;
    wait -= SDL_GetTicks();
    // std::cout << wait << std::endl;
    wait = std::max(0, wait);
    SDL_Delay(wait);
}
