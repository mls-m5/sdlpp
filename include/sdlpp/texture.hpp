#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>

namespace sdl {

struct Texture : detail::UniquePtr<SDL_Texture, SDL_DestroyTexture> {
    using UniquePtr::UniquePtr;

    Texture(SDL_Renderer *renderer, Uint32 format, int access, int w, int h) {
        SDL_CreateTexture(renderer, format, access, w, h);
    }

    void colorMod(Uint8 r, Uint8 g, Uint8 b) {
        SDL_SetTextureColorMod(get(), r, g, b);
    }

    void alphaMod(Uint8 mod) {
        SDL_SetTextureAlphaMod(get(), mod);
    }
};

} // namespace sdl
