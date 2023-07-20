// Note to use this header you need to link against SDL2_image

#pragma once

#include "SDL2/SDL_image.h"
#include "render.hpp"
#include "surface.hpp"
#include "texture.hpp"

namespace img {

void init(int flags) {
    IMG_Init(flags);
}

void quit() {
    IMG_Quit();
}

sdl::Surface load(const char *path) {
    return sdl::Surface{IMG_Load(path)};
}

sdl::Texture loadTexture(sdl::RendererView renderer, const char *path) {
    return sdl::Texture{IMG_LoadTexture(renderer.get(), path)};
}

int savePng(sdl::SurfaceView surface, const char *path) {
    return IMG_SavePNG(surface.get(), path);
}

int saveJpg(sdl::SurfaceView surface, const char *path, int quality) {
    return IMG_SaveJPG(surface.get(), path, quality);
}

} // namespace img
