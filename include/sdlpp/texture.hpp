#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>

namespace sdl {

struct Texture : detail::UniquePtr<SDL_Texture, SDL_DestroyTexture> {
    using UniquePtr::UniquePtr;

    Texture(SDL_Renderer *renderer, Uint32 format, int access, int w, int h) {
        SDL_CreateTexture(renderer, format, access, w, h);
    }
};

} // namespace sdl
