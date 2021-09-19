#pragma once

#include "detail/uniqueptr.hpp"
#include <SDL2/SDL_render.h>

namespace sdl {

namespace detail {

template <typename Container>
struct TextureImpl : Container {
    using Container::Container;

    TextureImpl(
        SDL_Renderer *renderer, Uint32 format, int access, int w, int h) {
        SDL_CreateTexture(renderer, format, access, w, h);
    }

    void colorMod(Uint8 r, Uint8 g, Uint8 b) {
        SDL_SetTextureColorMod(this->get(), r, g, b);
    }

    void alphaMod(Uint8 mod) {
        SDL_SetTextureAlphaMod(this->get(), mod);
    }

    void colorMod(SDL_Color color) {
        SDL_SetTextureColorMod(this->get(), color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(this->get(), color.a);
    }
};

} // namespace detail

using Texture =
    detail::TextureImpl<detail::UniquePtr<SDL_Texture, SDL_DestroyTexture>>;
using TextureView = detail::TextureImpl<detail::View<SDL_Texture>>;

} // namespace sdl
