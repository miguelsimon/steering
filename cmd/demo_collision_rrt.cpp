#include "CollisionRRTWorld.h"
#include "demo.h"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
    auto world = CollisionRRTWorld();

    auto [win, ren] = demo_setup_sdl();

    DemoState state{(World *)&world, win, ren, SDL_GetTicks(), false};

    std::cout << "Click anywhere to set a starting point." << std::endl;
    std::cout << std::endl;
    std::cout
        << "RRT random samples are drawn uniformly from the rectangular region."
        << std::endl;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(demo_sync_main_loop, &state, 0, true);
#else
    while (!state.quit) {
        demo_sync_main_loop(&state);
    }
#endif
}
