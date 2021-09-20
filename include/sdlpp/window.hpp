#pragma once

#include "detail/uniqueptr.hpp"
#include "rect.hpp"
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

    inline void size(int width, int height) {
        SDL_SetWindowSize(this->get(), width, height);
    }

    inline sdl::Dims size() {
        auto dims = sdl::Dims{};
        SDL_SetWindowSize(this->get(), dims.w, dims.h);
        return dims;
    }

    inline void title(const char *title) {
        SDL_SetWindowTitle(this->get(), title);
    }

    inline char *title() {
        SDL_GetWindowTitle(this->get());
    }
};

} // namespace detail

using Window =
    detail::WindowImpl<detail::UniquePtr<SDL_Window, SDL_DestroyWindow>>;

using WindowView = detail::WindowImpl<detail::View<SDL_Window>>;

} // namespace sdl
