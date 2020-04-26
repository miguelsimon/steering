#ifndef DEMO_H
#define DEMO_H

#include "world.h"
#include <SDL.h>

struct DemoState {
    World *world;
    SDL_Window *win;
    SDL_Renderer *ren;
    unsigned int sim_time;
    bool quit;
};

void demo_main_loop(void *);
void demo_sync_main_loop(void *);

auto demo_setup_sdl() -> std::tuple<SDL_Window *, SDL_Renderer *>;

#endif
