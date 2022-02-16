#pragma once

#include "SDL2/SDL.h"

namespace sdl {

/**
 *  This function initializes  the subsystems specified by \c flags
 */
int init(Uint32 flags) {
    return SDL_Init(flags);
}

/**
 *  This function initializes specific SDL subsystems
 *
 *  Subsystem initialization is ref-counted, you must call
 *  SDL_QuitSubSystem() for each SDL_InitSubSystem() to correctly
 *  shutdown a subsystem manually (or call SDL_Quit() to force shutdown).
 *  If a subsystem is already loaded then this call will
 *  increase the ref-count and return.
 */
int initSub(Uint32 flags) {
    return SDL_InitSubSystem(flags);
}

/**
 *  This function cleans up specific SDL subsystems
 */
void quitSubSystem(Uint32 flags) {
    SDL_QuitSubSystem(flags);
}

/**
 *  This function returns a mask of the specified subsystems which have
 *  previously been initialized.
 *
 *  If \c flags is 0, it returns a mask of all initialized subsystems.
 */
Uint32 wasInit(Uint32 flags) {
    return SDL_WasInit(flags);
}

/**
 *  This function cleans up all initialized subsystems. You should
 *  call it upon all exit conditions.
 */
void quit() {
    SDL_Quit();
}

} // namespace sdl
