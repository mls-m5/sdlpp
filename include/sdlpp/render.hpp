#pragma once

#include "rect.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include <SDL2/SDL_render.h>
#include <optional>

namespace sdl {
namespace detail {

template <typename Container>
struct RendererImpl : public Container {
    RendererImpl(SDL_Window *window, int index, Uint32 flags)
        : Container{SDL_CreateRenderer(window, index, flags)} {}

    using Container::Container;

    inline void clear() {
        SDL_RenderClear(this->get());
    }

    inline void drawColor(SDL_Color color) {
        SDL_SetRenderDrawColor(this->get(), color.r, color.g, color.b, color.a);
    }

    inline void drawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        SDL_SetRenderDrawColor(this->get(), r, g, b, a);
    }

    inline void fillRect(const SDL_Rect &rect) {
        SDL_RenderFillRect(this->get(), &rect);
    }

    inline void fillRect() {
        SDL_RenderFillRect(this->get(), nullptr);
    }

    inline void drawLine(int x1, int y1, int x2, int y2) {
        SDL_RenderDrawLine(this->get(), x1, y1, x2, y2);
    }

    template <typename T>
    inline void drawPoint(const T &point) {
        SDL_RenderDrawPoint(this->get(), point.x, point.y);
    }

    template <typename T>
    inline void drawPointF(const T &point) {
        SDL_RenderDrawPointF(this->get(), point.x, point.y);
    }

    template <typename T>
    inline void drawPoints(const T &points) {
        SDL_RenderDrawPoints(this->get(), points->get(), points.size());
    }

    template <typename T>
    inline void drawPointsF(const T &points) {
        SDL_RenderDrawPointsF(this->get(), points->get(), points.size());
    }

    inline void present() {
        SDL_RenderPresent(this->get());
    }

    inline void copy(SDL_Texture *texture, const SDL_Rect &dstrect) {
        SDL_RenderCopy(this->get(), texture, {}, &dstrect);
    }

    inline void copy(SDL_Texture *texture,
                     const SDL_Rect &srcrect,
                     const SDL_Rect &dstrect) {
        SDL_RenderCopy(this->get(), texture, &srcrect, &dstrect);
    }

    inline void copy(SDL_Texture *texture,
                     const SDL_Rect *srcrect,
                     const SDL_Rect *dstrect) {
        SDL_RenderCopy(this->get(), texture, srcrect, dstrect);
    }

    inline void copyEx(SDL_Texture *texture,
                       const SDL_Rect *srcrect,
                       const SDL_Rect *dstrect,
                       const double angle,
                       const SDL_Point *center,
                       const SDL_RendererFlip flip) {
        SDL_RenderCopyEx(
            this->get(), texture, srcrect, dstrect, angle, center, flip);
    }

    inline Texture createTextureFromSurface(SDL_Surface *surface) {
        return {SDL_CreateTextureFromSurface(this->get(), surface)};
    }

    inline Dims getOutputSize() {
        Dims dims;
        SDL_GetRendererOutputSize(this->get(), &dims.w, &dims.h);
        return dims;
    }

    inline void drawBlendMode(SDL_BlendMode mode) {
        SDL_SetRenderDrawBlendMode(this->get(), mode);
    }

    inline std::optional<SDL_BlendMode> drawBlendMode() {
        SDL_BlendMode mode;
        if (!SDL_GetRenderDrawBlendMode(this->get(), &mode)) {
            return mode;
        }
        else {
            return {};
        }
    }

    inline int renderTarget(SDL_Texture *texture) {
        return SDL_SetRenderTarget(this->get(), texture);
    }

    inline operator RendererImpl<detail::View<SDL_Renderer>>() {
        return RendererImpl<detail::View<SDL_Renderer>>{this->get()};
    }

    inline int scale(float x, float y) {
        return SDL_RenderSetScale(this->get(), x, y);
    }

    inline std::pair<float, float> scale() {
        float x = 0, y = 0;
        SDL_RenderGetScale(this->get(), &x, &y);
        return {x, y};
    }

    int blendMode(SDL_BlendMode mode) {
        return SDL_SetRenderDrawBlendMode(this->get(), mode);
    }

    SDL_BlendMode blendMode() {
        SDL_BlendMode mode = {};
        SDL_GetRenderDrawBlendMode(this->get(), &mode);
        return mode;
    }
};

} // namespace detail

using Renderer =
    detail::RendererImpl<detail::UniquePtr<SDL_Renderer, SDL_DestroyRenderer>>;
using RendererView = detail::RendererImpl<detail::View<SDL_Renderer>>;

} // namespace sdl
