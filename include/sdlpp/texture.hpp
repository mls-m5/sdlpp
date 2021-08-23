#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>

namespace sdl {

struct Texture : detail::UniquePtr<SDL_Texture, SDL_DestroyTexture> {};

} // namespace sdl
