#pragma once

#include "detail/uniqueptr.hpp"
#include "pixels.hpp"
#include "rect.hpp"
#include <SDL2/SDL_render.h>
#include <memory>
#include <optional>
#include <string_view>

namespace sdl {

namespace detail {

template <typename Container>
struct SurfaceImpl : Container {
    using Container::Container;

    SurfaceImpl(Uint32 flags,
                int width,
                int height,
                int depth,
                Uint32 Rmask,
                Uint32 Gmask,
                Uint32 Bmask,
                Uint32 Amask)
        : Container{SurfaceImpl::create(
              flags, width, height, depth, Rmask, Gmask, Bmask, Amask)} {}

    inline int lock() {
        return SDL_LockSurface(this->get());
    }

    inline void unlock() {
        SDL_UnlockSurface(this->get());
    }

    //! Get single comoponent of a pixel
    //! Remember to call load() before and unload() after
    //! Get pixel depth by using
    //! Also check if surface if RGB or BGR etc
    //! Get depth by format->BytesPerPixel
    inline uint8_t &pixelData(size_t x, size_t y, size_t bit, size_t depth) {
        auto p = reinterpret_cast<uint8_t *>(this->get()->pixels);
        return p[y * this->get()->pitch + x * depth + bit];
    }

    inline void setColorKey(int flag, Uint32 key) {
        SDL_SetColorKey(this->get(), flag, key);
    }

    inline bool hasColorKey() {
        return SDL_HasColorKey(this->get());
    }

    inline int getColorKey(Uint32 *key) {
        return SDL_GetColorKey(this->get(), key);
    }

    static inline SurfaceImpl create(Uint32 flags,
                                     int width,
                                     int height,
                                     int depth,
                                     Uint32 Rmask,
                                     Uint32 Gmask,
                                     Uint32 Bmask,
                                     Uint32 Amask) {
        return {SDL_CreateRGBSurface(
            flags, width, height, depth, Rmask, Gmask, Bmask, Amask)};
    }

    static inline SurfaceImpl createWithFormat(
        Uint32 flags, int width, int height, int depth, Uint32 format) {
        return {SDL_CreateRGBSurfaceWithFormat(
            flags, width, height, depth, format)};
    }

    static inline SurfaceImpl createFrom(void *pixels,
                                         int width,
                                         int height,
                                         int depth,
                                         int pitch,
                                         Uint32 Rmask,
                                         Uint32 Gmask,
                                         Uint32 Bmask,
                                         Uint32 Amask) {
        return {SDL_CreateRGBSurfaceFrom(
            pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask)};
    }

    static inline SurfaceImpl createWithFormatFrom(void *pixels,
                                                   int width,
                                                   int height,
                                                   int depth,
                                                   int pitch,
                                                   Uint32 format) {
        return {SDL_CreateRGBSurfaceWithFormatFrom(
            pixels, width, height, depth, pitch, format)};
    }

    int saveBMP(const char *file) {
        return SDL_SaveBMP_RW(this->get(), SDL_RWFromFile(file, "wb"), 1);
    }

    /**
     *  \brief Sets the RLE acceleration hint for a surface.
     *
     *  \return 0 on success, or -1 if the surface is not valid
     *
     *  \note If RLE is enabled, colorkey and alpha blending blits are much
     * faster, but the surface must be locked before directly accessing the
     * pixels.
     */
    int rle(int flag) {
        return SDL_SetSurfaceRLE(this->get(), flag);
    }

    /**
     *  \brief Set an additional color value used in blit operations.
     *
     *  \param surface The surface to update.
     *  \param r The red color value multiplied into blit operations.
     *  \param g The green color value multiplied into blit operations.
     *  \param b The blue color value multiplied into blit operations.
     *
     *  \return 0 on success, or -1 if the surface is not valid.
     *
     *  \sa SDL_GetSurfaceColorMod()
     */
    int colorMod(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b) {
        return SDL_SetSurfaceColorMod(this->get(), r, g, b);
    }

    int colorMod(SDL_Surface *surface, Color color) {
        return SDL_SetSurfaceColorMod(this->get(), color.r, color.g, color.b);
    }

    //! a is ignored
    std::optional<Color> colorMod() {
        auto color = Color{};
        if (SDL_GetSurfaceColorMod(this->get(), &color.r, &color.g, &color.b)) {
            return std::nullopt;
        }

        return color;
    }

    /**
     *  \brief Set an additional alpha value used in blit operations.
     *
     *  \param surface The surface to update.
     *  \param alpha The alpha value multiplied into blit operations.
     *
     *  \return 0 on success, or -1 if the surface is not valid.
     *
     *  \sa SDL_GetSurfaceAlphaMod()
     */
    int surfaceAlpha(Uint8 alpha) {
        return SDL_SetSurfaceAlphaMod(this->get(), alpha);
    }

    /**
     *  \brief Get the additional alpha value used in blit operations.
     *
     *  \param surface The surface to query.
     *  \param alpha A pointer filled in with the current alpha value.
     *
     *  \return value on success std::nullopt on fail
     *
     *  \sa SDL_SetSurfaceAlphaMod()
     */
    std::optional<int> surfaceAlpha() {
        auto alpha = int{0};
        if (SDL_GetSurfaceAlphaMod(this->get(), &alpha)) {
            return std::nullopt;
        }

        return alpha;
    }

    void fillRect(std::optional<sdl::Rect> rect, sdl::Color color) {
        SDL_FillRect(this->get(),
                     rect ? &*rect : nullptr,
                     reinterpret_cast<Uint32 &>(color));
    }

    int blendMode(SDL_BlendMode mode) {
        return SDL_SetSurfaceBlendMode(this->get(), mode);
    }

    std::optional<SDL_BlendMode> surfaceBlendMode() {
        auto mode = SDL_BlendMode{};
        if (SDL_GetSurfaceBlendMode(this->get(), &mode)) {
            return std::nullopt;
        }

        return mode;
    }

    bool clipRect(std::optional<sdl::Rect> rect) {
        return SDL_SetClipRect(this->get(), (rect ? &(*rect) : nullptr));
    }

    std::optional<sdl::Rect> clipRect() {
        auto rect = sdl::Rect{};
        if (SDL_GetClipRect(this->get(), &rect)) {
            return std::nullopt;
        }
        return rect;
    }

    // Todo: Add more functions here.

    //! Blit another surface to this surface
    int blit(SurfaceImpl<detail::View<SDL_Surface>> src,
             std::optional<sdl::Rect> srcRect = {},
             std::optional<sdl::Rect> dstRect = {}) {
        return SDL_BlitSurface(src.get(),
                               srcRect ? &*srcRect : nullptr,
                               this->get(),
                               dstRect ? &*dstRect : nullptr);
    }

    /**
     *  \brief Perform a fast, low quality, stretch blit between two surfaces of
     * the same pixel format.
     *
     *  \note This function uses a static buffer, and is not thread-safe.
     */
    int softStretch(SurfaceImpl<detail::View<SDL_Surface>> src,
                    std::optional<sdl::Rect> srcRect = {},
                    std::optional<sdl::Rect> dstRect = {}) {
        return SDL_SoftStretch(src.get(),
                               srcRect ? &*srcRect : nullptr,
                               this->get(),
                               dstRect ? &*dstRect : nullptr);
    }

    int blitScaled(SurfaceImpl<detail::View<SDL_Surface>> src,
                   std::optional<sdl::Rect> srcRect = {},
                   std::optional<sdl::Rect> dstRect = {}) {
        return SDL_BlitScaled(src.get(),
                              srcRect ? &*srcRect : nullptr,
                              this->get(),
                              dstRect ? &*dstRect : nullptr);
    }

    SurfaceImpl<detail::UniquePtr<SDL_Surface, SDL_FreeSurface>> duplicate() {
        return {SDL_DuplicateSurface(this->get())};
    }
};

} // namespace detail

using Surface =
    detail::SurfaceImpl<detail::UniquePtr<SDL_Surface, SDL_FreeSurface>>;

using SurfaceView = detail::SurfaceImpl<detail::View<SDL_Surface>>;

inline Surface loadBmp(std::string_view data) {
    return Surface{SDL_LoadBMP(data.data())};
}

} // namespace sdl
