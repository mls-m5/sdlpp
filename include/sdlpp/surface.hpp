#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>
#include <memory>

namespace sdl {

namespace detail {

template <typename Container>
struct SurfaceImpl : Container {};

} // namespace detail

using Surface =
    detail::SurfaceImpl<detail::UniquePtr<SDL_Surface, SDL_FreeSurface>>;

using SurfaceView = detail::SurfaceImpl<detail::View<SDL_Surface>>;

inline Surface loadBmp(std::string_view data) {
    return Surface{SDL_LoadBMP(data.data())};
}

} // namespace sdl
