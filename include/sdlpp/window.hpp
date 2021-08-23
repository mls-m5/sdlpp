#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_video.h>

namespace sdl {

struct Window : public detail::UniquePtr<SDL_Window, SDL_DestroyWindow> {
    Window(const char *title, int x, int y, int w, int h, Uint32 flags)
        : UniquePtr{SDL_CreateWindow(title, x, x, w, h, flags)} {}

    inline void show() {
        SDL_ShowWindow(get());
    }

    ~Window() {
        SDL_DestroyWindow(get());
    }
};

} // namespace sdl
