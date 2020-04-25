#include "WaypointWorld.h"
#include "demo.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
    auto world = WaypointWorld();

    auto [win, ren] = demo_setup_sdl();

    DemoState state{(World *)&world, win, ren, SDL_GetTicks(), false};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(demo_main_loop, &state, 0, true);
#else
    while (!state.quit) {
        demo_main_loop(&state);
    }
#endif
}
