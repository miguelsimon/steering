#include "demo.h"
#include "draw.h"
#include <iostream>

auto demo_setup_sdl() -> std::tuple<SDL_Window *, SDL_Renderer *> {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Window *win =
        SDL_CreateWindow("Hello World!", 100, 100, 620, 387, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        std::cout << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
        exit(1);
    }

    return std::make_tuple(win, ren);
}

void demo_main_loop(void *arg) {
    auto *state = static_cast<DemoState *>(arg);

    Draw draw = Draw(state->ren);
    draw.clear();

    state->world->render(draw);
    SDL_RenderPresent(state->ren);

    // sleep if there's time to spare before next step
    long wait = state->sim_time;
    wait -= SDL_GetTicks();
    wait = std::max(0l, wait);
    SDL_Delay(wait);

    // catch up simulation
    while (state->sim_time < SDL_GetTicks()) {
        state->world->step();
        state->sim_time += (int)state->world->get_step_milliseconds();
    };

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            state->quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {

            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);

            state->world->click((float)x, (float)y);
        }
    }
}
