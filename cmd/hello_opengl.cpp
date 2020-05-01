// learn how to setup gl context that works both locally & in the browser

#ifdef __EMSCRIPTEN__

#include <GL/gl.h>
#include <emscripten.h>

#else

#include <glad/gl.h>

#endif

#include <SDL.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define WinWidth 1000
#define WinHeight 1000

bool quit;
SDL_Window *Window;
SDL_GLContext Context;

void main_loop(void *arg);

int main(int ArgCount, char **Args) {

    u32 WindowFlags = SDL_WINDOW_OPENGL;
    Window =
        SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
    assert(Window);

    Context = SDL_GL_CreateContext(Window);
    if (!Context) {
        fprintf(stderr, "Failed to initialize WebGL context!\n");
        return 1;
    }
    fprintf(stderr, "Initialized!\n");

// Emscripten wnats to be statically linked
// otherwise load using glad,
// see https://github.com/Dav1dde/glad-web/issues/12
#ifndef __EMSCRIPTEN__
    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version),
           GLAD_VERSION_MINOR(version));
#endif

// emscripten needs control of the mainloop, otherwise just loop
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(main_loop, NULL, 0, true);
#else
    while (!quit)
        main_loop(NULL);
#endif

    return 0;
}

void main_loop(void *arg) {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_QUIT) {
            quit = true;
        };
    };

    glViewport(0, 0, WinWidth, WinHeight);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(Window);
};
