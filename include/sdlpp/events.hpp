#pragma once

#include "SDL2/SDL_events.h"
#include <optional>

namespace sdl {

using Event = SDL_Event;

std::optional<SDL_Event> pollEvent() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        return {event};
    }
    else {
        return {};
    }
}

//! Example usage
//! ```c++
//! auto running = true;
//! for (std::optional<SDL_Event> o; (o = sdl::waitEvent()) && running;) {
//! auto event = *o;
//!
//! switch (event.type) {
//! case SDL_QUIT:
//!     running = false;
//!     break;
//! }
//! }
//! ```
SDL_Event waitEvent() {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        return {event};
    }
    else {
        return {};
    }
}

// @ param timeout   timeout in ms
std::optional<SDL_Event> waitEventTimeout(int timeout) {
    SDL_Event event;
    if (SDL_WaitEventTimeout(&event, timeout)) {
        return {event};
    }
    else {
        return {};
    }
}

int pushEvent(SDL_Event &event) {
    return SDL_PushEvent(&event);
}

} // namespace sdl
