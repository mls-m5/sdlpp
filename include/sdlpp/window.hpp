#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_video.h>

namespace sdl {

namespace detail {

template <typename Container>
struct WindowImpl : public Container {
    WindowImpl(const char *title, int x, int y, int w, int h, Uint32 flags)
        : Container{SDL_CreateWindow(title, x, x, w, h, flags)} {}

    inline void show() {
        SDL_ShowWindow(this->get());
    }
};

} // namespace detail

using Window =
    detail::WindowImpl<detail::UniquePtr<SDL_Window, SDL_DestroyWindow>>;

using WindowView = detail::WindowImpl<detail::View<SDL_Window>>;

} // namespace sdl
