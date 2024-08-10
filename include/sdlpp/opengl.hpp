// Opengl related functions from "SDL_video.h"

#pragma once

#include "SDL2/SDL_video.h"
#include "detail/uniqueptr.hpp"
#include "window.hpp"
#include <optional>

namespace sdl {
namespace gl {

namespace detail {

using GLContextPtrT = std::remove_pointer_t<SDL_GLContext>;

template <typename Container>
struct ContextImpl : Container {
    using Container::Container;

    ContextImpl(sdl::WindowView window)
        : Container{SDL_GL_CreateContext(window)} {
    }

    int makeCurrent(sdl::WindowView window) {
        return SDL_GL_MakeCurrent(window.get(), this->get());
    }

    static detail::ContextImpl<sdl::detail::View<detail::GLContextPtrT>>
    current() {
        return SDL_GL_GetCurrentContext();
    }
};

} // namespace detail

/// Owning pointer type
using Context = detail::ContextImpl<
    sdl::detail::UniquePtr<detail::GLContextPtrT, SDL_GL_DeleteContext>>;

/// Non owning pointer type
using ContextView =
    detail::ContextImpl<sdl::detail::View<detail::GLContextPtrT>>;

inline void resetAttributes() {
    SDL_GL_ResetAttributes();
}

inline int setAttribute(SDL_GLattr attr, int value) {
    return SDL_GL_SetAttribute(attr, value);
}

inline std::optional<int> getAttribute(SDL_GLattr attr) {
    int val = 0;
    if (!SDL_GL_GetAttribute(attr, &val)) {
        return {val};
    }
    return {};
}

inline int setSwapInterval(int interval) {
    return SDL_GL_SetSwapInterval(interval);
}

inline int getSwapInterval() {
    return SDL_GL_GetSwapInterval();
}

inline int enableDebugPrint() {
    return SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
}

} // namespace gl
} // namespace sdl
