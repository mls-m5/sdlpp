#pragma once

#include <memory>

namespace sdl {

namespace detail {

template <typename Type, void (*DestroyFunction)(Type *)>
struct Deleter {
    void operator()(Type *ptr) {
        DestroyFunction(ptr);
    }
};

template <typename Type, void (*DestroyFunction)(Type *)>
struct UniquePtr;

// Non owning pointer type
template <typename Type>
struct View {
    using ViewT = View;
    Type *ptr = {};

    View(Type *value)
        : ptr(value) {}

    template <typename T>
    View(T &other)
        : ptr(other.get()) {}

    View() = default;
    View(const View &) = default;
    View(View &&) = default;
    View &operator=(const View &) = default;
    View &operator=(View &&) = default;

    operator Type *() {
        return ptr;
    }

    Type *get() {
        return ptr;
    }

    const Type *get() const {
        return ptr;
    }

    Type *operator->() {
        return ptr;
    }

    const Type *operator->() const {
        return ptr;
    }
};

// shorthand notation for unique pointer with specified destructor function
template <typename Type, void (*DestroyFunction)(Type *)>
struct UniquePtr : std::unique_ptr<Type, Deleter<Type, DestroyFunction>> {
    using std::unique_ptr<Type, Deleter<Type, DestroyFunction>>::unique_ptr;
    using ViewT = View<Type>;

    UniquePtr(Type *value) {
        this->reset(value);
    }

    // Implicit conversion to underlying pointer type
    operator Type *() {
        return this->get();
    }

    operator ViewT() {
        return {this->get()};
    }

    Type *release() {
        return this
            ->std::unique_ptr<Type, Deleter<Type, DestroyFunction>>::release();
    }
};

} // namespace detail

} // namespace sdl
