#pragma once

#include "SDL2/SDL_events.h"
#include <optional>

namespace sdl {

std::optional<SDL_Event> pollEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        return {event};
    }
    else {
        return {};
    }
}

} // namespace sdl
