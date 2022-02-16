#pragma once

#include "SDL2/SDL_timer.h"

namespace sdl {

/**
 * \brief Get the number of milliseconds since the SDL library initialization.
 *
 * \note This value wraps if the program runs for more than ~49 days.
 */
inline Uint32 getTicks() {
    return SDL_GetTicks();
}

/**
 * \brief Compare SDL ticks values, and return true if A has passed B
 *
 * e.g. if you want to wait 100 ms, you could do this:
 *  Uint32 timeout = SDL_GetTicks() + 100;
 *  while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
 *      ... do work until timeout has elapsed
 *  }
 */
inline constexpr bool ticksPassed(Sint32 a, Sint32 b) {
    return b - a <= 0;
}

/**
 * \brief Get the current value of the high resolution counter
 */
inline Uint64 getPerformanceCounter() {
    return SDL_GetPerformanceCounter();
}

/**
 * \brief Get the count per second of the high resolution counter
 */
inline Uint64 getPerformanceFrequency() {
    return SDL_GetPerformanceFrequency();
}

/**
 * \brief Wait a specified number of milliseconds before returning.
 */
inline void delay(Uint32 ms) {
    return SDL_Delay(ms);
}

/**
 *  Function prototype for the timer callback function.
 *
 *  The callback function is passed the current timer interval and returns
 *  the next timer interval.  If the returned value is the same as the one
 *  passed in, the periodic alarm continues, otherwise a new alarm is
 *  scheduled.  If the callback returns 0, the periodic alarm is cancelled.
 */
using TimerCallback = Uint32(SDLCALL *)(Uint32 interval, void *param);

/**
 * Definition of the timer ID type.
 */
using TimerId = SDL_TimerID;

/**
 * \brief Add a new timer to the pool of timers already running.
 *
 * \return A timer ID, or 0 when an error occurs.
 */
inline TimerId addTimer(Uint32 interval, TimerCallback callback, void *param) {
    return SDL_AddTimer(interval, callback, param);
}

/**
 * \brief Remove a timer knowing its ID.
 *
 * \return A boolean value indicating success or failure.
 *
 * \warning It is not safe to remove a timer multiple times.
 */
inline bool removeTimer(TimerId id) {
    return SDL_RemoveTimer(id);
}

} // namespace sdl
