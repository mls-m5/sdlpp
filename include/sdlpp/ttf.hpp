#pragma once

#include "SDL2/SDL_ttf.h"
#include "pixels.hpp"
#include "rect.hpp"
#include "surface.hpp"

namespace ttf {

struct Font : public sdl::detail::UniquePtr<TTF_Font, TTF_CloseFont> {
    using UniquePtr::UniquePtr;

    Font(const char *file, int ptsize) : UniquePtr{TTF_OpenFont(file, ptsize)} {
    }

    inline int style() const {
        return TTF_GetFontStyle(get());
    }

    inline void style(int style) {
        TTF_SetFontStyle(get(), style);
    }

    inline int outline() const {
        return TTF_GetFontOutline(get());
    }

    inline void outline(int outline) {
        return TTF_SetFontOutline(get(), outline);
    }

    inline int hinting() const {
        return TTF_GetFontHinting(get());
    }

    inline void hinting(int hinting) {
        TTF_SetFontHinting(get(), hinting);
    }

    inline int height() const {
        return TTF_FontHeight(get());
    }

    inline int ascent() const {
        return TTF_FontAscent(get());
    }

    inline int descent() {
        return TTF_FontDescent(get());
    }

    inline int lineSkip() const {
        return TTF_FontLineSkip(get());
    }

    inline int kerning() const {
        return TTF_GetFontKerning(get());
    }

    inline void kerning(int kerning) {
        return TTF_SetFontKerning(get(), kerning);
    }

    inline int faces() const {
        return TTF_FontFaces(get());
    }

    inline int faceIsFixedWidth() const {
        return TTF_FontFaceIsFixedWidth(get());
    }

    inline const char *faceFamilyName() const {
        return TTF_FontFaceFamilyName(get());
    }

    inline const char *faceStyleName() const {
        return TTF_FontFaceStyleName(get());
    }

    inline int glyphIsProvided(Uint16 ch) const {
        return TTF_GlyphIsProvided(get(), ch);
    }

    struct Metrics {
        int minx;
        int maxx;
        int miny;
        int maxy;
        int advance;
    };

    inline Metrics glyphMetrics(Uint16 ch) {
        auto metrics = Metrics{};
        TTF_GlyphMetrics(get(),
                         ch,
                         &metrics.minx,
                         &metrics.maxx,
                         &metrics.miny,
                         &metrics.maxy,
                         &metrics.advance);
        return metrics;
    }

    inline sdl::Dims sizeText(const char *text) const {
        auto dims = sdl::Dims{};
        TTF_SizeText(get(), text, &dims.w, &dims.h);
        return dims;
    }

    inline sdl::Dims sizeTextUtf8(const char *text) const {
        sdl::Dims dims{};
        TTF_SizeUTF8(get(), text, &dims.w, &dims.h);
        return dims;
    }

    inline sdl::Dims sizeTextUNICODE(const Uint16 *text) const {
        sdl::Dims dims{};
        TTF_SizeUNICODE(get(), text, &dims.w, &dims.h);
        return dims;
    }

    inline sdl::Surface renderTextSolid(const char *text, sdl::Color fg) {
        return {TTF_RenderText_Solid(get(), text, fg)};
    }
    inline sdl::Surface renderUTF8Solid(const char *text, sdl::Color fg) {
        return {TTF_RenderUTF8_Solid(get(), text, fg)};
    }
    inline sdl::Surface renderUNICODESolid(const Uint16 *text, sdl::Color fg) {
        return {TTF_RenderUNICODE_Solid(get(), text, fg)};
    }

    inline sdl::Surface renderGlyphSolid(Uint16 ch, sdl::Color fg) {
        return {TTF_RenderGlyph_Solid(get(), ch, fg)};
    }

    inline sdl::Surface renderTextShaded(const char *text,
                                         sdl::Color fg,
                                         sdl::Color bg) {
        return {TTF_RenderText_Shaded(get(), text, fg, bg)};
    }
    inline sdl::Surface renderUTF8Shaded(const char *text,
                                         sdl::Color fg,
                                         sdl::Color bg) {
        return {TTF_RenderUTF8_Shaded(get(), text, fg, bg)};
    }
    inline sdl::Surface renderUNICODEShaded(const Uint16 *text,
                                            sdl::Color fg,
                                            sdl::Color bg) {
        return {TTF_RenderUNICODE_Shaded(get(), text, fg, bg)};
    }

    inline sdl::Surface renderGlyphShaded(Uint16 ch,
                                          sdl::Color fg,
                                          sdl::Color bg) {
        return {TTF_RenderGlyph_Shaded(get(), ch, fg, bg)};
    }

    inline sdl::Surface renderTextBlended(const char *text, sdl::Color fg) {
        return {TTF_RenderText_Blended(get(), text, fg)};
    }

    inline sdl::Surface renderUTF8Blended(const char *text, sdl::Color fg) {
        return {TTF_RenderUTF8_Blended(get(), text, fg)};
    }
    inline sdl::Surface renderUNICODEBlended(const Uint16 *text,
                                             sdl::Color fg) {
        return {TTF_RenderUNICODE_Blended(get(), text, fg)};
    }

    inline sdl::Surface renderText(const char *text, sdl::Color fg) {
        return renderTextBlended(text, fg);
    }
    inline sdl::Surface renderUTF8(const char *text, sdl::Color fg) {
        return renderUTF8Blended(text, fg);
    }
    inline sdl::Surface renderUNICODE(const Uint16 *text, sdl::Color fg) {
        return renderUNICODEBlended(text, fg);
    }

    inline sdl::Surface renderGlyphBlended(Uint16 ch, sdl::Color fg) {
        return {TTF_RenderGlyph_Blended(get(), ch, fg)};
    }

    inline sdl::Surface renderTextBlendedWrapped(const char *text,
                                                 sdl::Color fg,
                                                 Uint32 wrapLength) {
        return {TTF_RenderText_Blended_Wrapped(get(), text, fg, wrapLength)};
    }
    inline sdl::Surface renderUTF8BlendedWrapped(const char *text,
                                                 sdl::Color fg,
                                                 Uint32 wrapLength) {
        return {TTF_RenderUTF8_Blended_Wrapped(get(), text, fg, wrapLength)};
    }
    inline sdl::Surface renderUNICODEBlendedWrapped(const Uint16 *text,
                                                    sdl::Color fg,
                                                    Uint32 wrapLength) {
        return {TTF_RenderUNICODE_Blended_Wrapped(get(), text, fg, wrapLength)};
    }
};

inline int init() {
    return TTF_Init();
}

inline void quit() {
    TTF_Quit();
}

inline Font openFontIndex(const char *file, int ptsize, int index) {
    return Font{TTF_OpenFontIndex(file, ptsize, index)};
}

} // namespace ttf
