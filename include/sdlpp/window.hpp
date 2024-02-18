#pragma once

#include "detail/uniqueptr.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>

namespace sdl {

namespace detail {

template <typename Container>
struct WindowImpl : public Container {
    WindowImpl(const char *title, int x, int y, int w, int h, Uint32 flags)
        : Container{SDL_CreateWindow(title, x, x, w, h, flags)} {}

    using Container::Container;

    Uint32 id() {
        return SDL_GetWindowID(this->get());
    }

    inline void title(const char *title) {
        SDL_SetWindowTitle(this->get(), title);
    }

    inline char *title() {
        return SDL_GetWindowTitle(this->get());
    }

    void icon(detail::View<SDL_Window> icon) {
        SDL_SetWindowIcon(this->get(), icon.get());
    }

    void position(int x, int y) {
        SDL_SetWindowPosition(this->get(), x, y);
    }

    sdl::Point position() {
        auto pos = sdl::Point{};
        SDL_GetWindowPosition(this->get(), &pos.x, &pos.y);
        return pos;
    }

    inline void size(int width, int height) {
        SDL_SetWindowSize(this->get(), width, height);
    }

    inline sdl::Dims size() {
        auto dims = sdl::Dims{};
        SDL_GetWindowSize(this->get(), &dims.w, &dims.h);
        return dims;
    }

    inline void show() {
        SDL_ShowWindow(this->get());
    }

    void hide() {
        SDL_HideWindow(this->get());
    }

    void raise() {
        SDL_RaiseWindow(this->get());
    }

    void maximize() {
        SDL_MaximizeWindow(this->get());
    }

    void restore() {
        SDL_RestoreWindow(this->get());
    }

    int fullscreen(Uint32 flags) {
        return SDL_SetWindowFullscreen(this->get(), flags);
    }

    void warpMouse(int x, int y) {
        SDL_WarpMouseInWindow(this->get(), x, y);
    }

    /// Swap opengl buffers
    void swap() {
        SDL_GL_SwapWindow(this->get());
    }

    /// Return curent active OpenGL window
    static WindowImpl<View<SDL_Window>> current() {
        return SDL_GL_GetCurrentWindow();
    }

    /// Create a view (non owning) from a windows id
    static inline WindowImpl<View<SDL_Window>> fromId(Uint32 id) {
        return {SDL_GetWindowFromID(id)};
    }

    SurfaceView surface() {
        return {SDL_GetWindowSurface(this->get())};
    }

    int updateSurface() {
        return SDL_UpdateWindowSurface(this->get());
    }
};

} // namespace detail

using Window =
    detail::WindowImpl<detail::UniquePtr<SDL_Window, SDL_DestroyWindow>>;

using WindowView = detail::WindowImpl<detail::View<SDL_Window>>;

} // namespace sdl
