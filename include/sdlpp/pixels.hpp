#pragma once

#include "SDL2/SDL_pixels.h"

namespace sdl {

struct Color : public SDL_Color {};

constexpr auto White = Color{255, 255, 255, 255};
constexpr auto Black = Color{0, 0, 0, 255};
constexpr auto Red = Color{255, 0, 0, 255};
constexpr auto Green = Color{0, 255, 0, 255};
constexpr auto Blue = Color{0, 0, 255, 255};

} // namespace sdl
