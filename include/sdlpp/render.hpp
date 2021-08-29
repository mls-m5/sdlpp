#pragma once

#include "rect.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include <SDL2/SDL_render.h>
#include <optional>

namespace sdl {

struct Renderer : public detail::UniquePtr<SDL_Renderer, SDL_DestroyRenderer> {
    Renderer(SDL_Window *window, int index, Uint32 flags)
        : UniquePtr{SDL_CreateRenderer(window, index, flags)} {}

    inline void clear() {
        SDL_RenderClear(get());
    }

    inline void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        SDL_SetRenderDrawColor(get(), r, g, b, a);
    }

    inline void fillRect(const SDL_Rect &rect) {
        SDL_RenderFillRect(get(), &rect);
    }

    inline void fillRect() {
        SDL_RenderFillRect(get(), nullptr);
    }

    inline void drawLine(int x1, int y1, int x2, int y2) {
        SDL_RenderDrawLine(get(), x1, y1, x2, y2);
    }

    template <typename T>
    inline void drawPoint(const T &point) {
        SDL_RenderDrawPoint(get(), point.x, point.y);
    }

    template <typename T>
    inline void drawPointF(const T &point) {
        SDL_RenderDrawPoint(get(), point.x, point.y);
    }

    template <typename T>
    inline void drawPoints(const T &points) {
        SDL_RenderDrawPoints(get(), points.get(), points.size());
    }

    template <typename T>
    inline void drawPointsF(const T &points) {
        SDL_RenderDrawPointsF(get(), points.get(), points.size());
    }

    inline void present() {
        SDL_RenderPresent(get());
    }

    inline void copy(SDL_Texture *texture,
                     const SDL_Rect &srcrect,
                     const SDL_Rect &dstrect) {
        SDL_RenderCopy(get(), texture, &srcrect, &dstrect);
    }

    inline void copy(SDL_Texture *texture,
                     const SDL_Rect *srcrect,
                     const SDL_Rect *dstrect) {
        SDL_RenderCopy(get(), texture, srcrect, dstrect);
    }

    inline void copyEx(SDL_Texture *texture,
                       const SDL_Rect *srcrect,
                       const SDL_Rect *dstrect,
                       const double angle,
                       const SDL_Point *center,
                       const SDL_RendererFlip flip) {
        SDL_RenderCopyEx(get(), texture, srcrect, dstrect, angle, center, flip);
    }

    inline Texture createTextureFromSurface(SDL_Surface *surface) {
        return {SDL_CreateTextureFromSurface(get(), surface)};
    }

    inline Dims getOutputSize() {
        Dims dims;
        SDL_GetRendererOutputSize(get(), &dims.w, &dims.h);
        return dims;
    }

    inline void drawBlendMode(SDL_BlendMode mode) {
        SDL_SetRenderDrawBlendMode(get(), mode);
    }

    inline std::optional<SDL_BlendMode> drawBlendMode() {
        SDL_BlendMode mode;
        if (!SDL_GetRenderDrawBlendMode(get(), &mode)) {
            return mode;
        }
        else {
            return {};
        }
    }

    void fillLine();
};

} // namespace sdl
