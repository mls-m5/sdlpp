#pragma once

#include <memory>

namespace sdl {

namespace detail {

template <typename Type, void (*DestroyFunction)(Type *)>
struct Deleter {
    void operator()(Type *texture) {
        DestroyFunction(texture);
    }
};

// shorthand notation for unique pointer with specified destructor function
template <typename Type, void (*DestroyFunction)(Type *)>
struct UniquePtr : std::unique_ptr<Type, Deleter<Type, DestroyFunction>> {
    using std::unique_ptr<Type, Deleter<Type, DestroyFunction>>::unique_ptr;

    UniquePtr(Type *value) {
        this->reset(value);
    }

    // Implicit conversion to underlying pointer type
    operator Type *() {
        return this->get();
    }
};

} // namespace detail

} // namespace sdl
