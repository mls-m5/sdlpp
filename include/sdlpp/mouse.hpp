#pragma once

#include "SDL2/SDL_mouse.h"

namespace sdl {

inline int showCursor(int toggle) {
    return SDL_ShowCursor(toggle);
}

inline int warpMouse(int x, int y) {
    return SDL_WarpMouseGlobal(x, y);
}

struct MouseState {
    Uint32 button;
    int x;
    int y;
};

inline MouseState getMouseState() {
    auto state = MouseState{};
    state.button = SDL_GetMouseState(&state.x, &state.y);
    return state;
}

inline MouseState getGlobalMouseState() {
    auto state = MouseState{};
    state.button = SDL_GetGlobalMouseState(&state.x, &state.y);
    return state;
}

} // namespace sdl
