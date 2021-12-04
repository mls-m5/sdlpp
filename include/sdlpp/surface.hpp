#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>
#include <memory>

namespace sdl {

namespace detail {

template <typename Container>
struct SurfaceImpl : Container {
    using Container::Container;

    SurfaceImpl(Uint32 flags,
                int width,
                int height,
                int depth,
                Uint32 Rmask,
                Uint32 Gmask,
                Uint32 Bmask,
                Uint32 Amask);

    inline int lock() {
        return SDL_LockSurface(this->get());
    }

    inline void unlock() {
        SDL_UnlockSurface(this->get());
    }

    inline void setColorKey(int flag, Uint32 key) {
        SDL_SetColorKey(this->get(), flag, key);
    }

    inline bool hasColorKey() {
        return SDL_HasColorKey(this->get());
    }

    inline int getColorKey(Uint32 *key) {
        SDL_GetColorKey(this->get(), key);
    }
};

} // namespace detail

using Surface =
    detail::SurfaceImpl<detail::UniquePtr<SDL_Surface, SDL_FreeSurface>>;

using SurfaceView = detail::SurfaceImpl<detail::View<SDL_Surface>>;

inline Surface loadBmp(std::string_view data) {
    return Surface{SDL_LoadBMP(data.data())};
}

inline Surface createRGBSurface(Uint32 flags,
                                int width,
                                int height,
                                int depth,
                                Uint32 Rmask,
                                Uint32 Gmask,
                                Uint32 Bmask,
                                Uint32 Amask) {
    return {SDL_CreateRGBSurface(
        flags, width, height, depth, Rmask, Gmask, Bmask, Amask)};
}

inline Surface createRGBSurfaceWithFormat(
    Uint32 flags, int width, int height, int depth, Uint32 format) {
    return {
        SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format)};
}

inline Surface createRGBSurfaceFrom(void *pixels,
                                    int width,
                                    int height,
                                    int depth,
                                    int pitch,
                                    Uint32 Rmask,
                                    Uint32 Gmask,
                                    Uint32 Bmask,
                                    Uint32 Amask) {
    return {SDL_CreateRGBSurfaceFrom(
        pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask)};
}

namespace detail {

template <typename Container>
SurfaceImpl<Container>::SurfaceImpl(Uint32 flags,
                                    int width,
                                    int height,
                                    int depth,
                                    Uint32 Rmask,
                                    Uint32 Gmask,
                                    Uint32 Bmask,
                                    Uint32 Amask)
    : Container{createRGBSurface(
          flags, width, height, depth, Rmask, Gmask, Bmask, Amask)} {}
} // namespace detail

} // namespace sdl
