#include "SeekWorld.h"
#include "demo.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
    SeekWorld seek_world = SeekWorld();

    auto [win, ren] = demo_setup_sdl();

    DemoState state{(World *)&seek_world, win, ren, SDL_GetTicks(), false};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(demo_main_loop, &state, 0, true);
#else
    while (!state.quit) {
        demo_main_loop(&state);
    }
#endif
}
