#pragma once

#include "SDL2/SDL_rect.h"

namespace sdl {

struct Rect : public SDL_Rect {
    inline bool empty() const {
        return SDL_RectEmpty(get());
    }

    inline friend bool operator==(const Rect &a, const Rect &b) {
        return SDL_RectEquals(a.get(), b.get());
    }

    inline friend bool hasIntersection(const Rect &a, const Rect &b) {
        return SDL_HasIntersection(a.get(), b.get());
    }

    inline Rect intersect(const Rect &other) const {
        Rect result;
        SDL_IntersectRect(get(), other.get(), result.get());
        return result;
    }

    inline Rect calculateUnion(const Rect &other) const {
        Rect result;
        SDL_UnionRect(get(), other.get(), result.get());
        return result;
    }

    const SDL_Rect *get() const {
        return this;
    }

    SDL_Rect *get() {
        return this;
    }
};

struct Point : public SDL_Point {
    bool inRect(const SDL_Rect &rect) const {
        return SDL_PointInRect(this, &rect);
    }

    SDL_Point *get() {
        return this;
    }
};

struct Dims {
    int w;
    int h;
};

} // namespace sdl
