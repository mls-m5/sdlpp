#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>
#include <memory>

namespace sdl {

struct Surface : detail::UniquePtr<SDL_Surface, SDL_FreeSurface> {};

inline Surface loadBmp(std::string_view data) {
    return Surface{SDL_LoadBMP(data.data())};
}

} // namespace sdl
