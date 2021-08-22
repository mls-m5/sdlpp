#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_video.h>

namespace sdl {

struct Window : public detail::UniquePtr<SDL_Window, SDL_DestroyWindow> {
    Window()
        : UniquePtr{SDL_CreateWindow(
              "Sdl stuff", 0, 0, 500, 500, SDL_WINDOW_SHOWN)} {}

    inline void show() {
        SDL_ShowWindow(get());
    }

    ~Window() {
        SDL_DestroyWindow(get());
    }
};

} // namespace sdl
