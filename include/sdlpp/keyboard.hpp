#pragma once

#include "rect.hpp"
#include <SDL2/SDL_keyboard.h>
#include <string_view>

namespace sdl {

SDL_Window *keyboardFocus() {
    return SDL_GetKeyboardFocus();
}

auto keyboardState() -> std::basic_string_view<Uint8> {
    auto len = int{};
    auto data = SDL_GetKeyboardState(&len);
    return {data, static_cast<size_t>(len)};
}

SDL_Keymod modState() {
    return SDL_GetModState();
}

void modState(SDL_Keymod modState) {
    SDL_SetModState(modState);
}

SDL_Keycode keyFromScancode(SDL_Scancode scancode) {
    return SDL_GetKeyFromScancode(scancode);
}

SDL_Scancode scancodeFromKey(SDL_Keycode keycode) {
    return SDL_GetScancodeFromKey(keycode);
}

std::string_view scancodeName(SDL_Scancode scancode) {
    return {SDL_GetScancodeName(scancode)};
}

SDL_Scancode scancodeFromName(const char *name) {
    return SDL_GetScancodeFromName(name);
}

SDL_Scancode scancodeFromName(std::string_view name) {
    return scancodeFromName(name.data());
}

std::string_view keyName(SDL_Keycode key) {
    return SDL_GetKeyName(key);
}

SDL_Keycode keyFromName(const char *name) {
    return SDL_GetKeyFromName(name);
}

SDL_Keycode keyFromName(std::string_view name) {
    return keyFromName(name.data());
}

void startTextInput() {
    SDL_StartTextInput();
}

bool isTextInputActive() {
    return SDL_IsTextInputActive();
}

void stopTextInput() {
    SDL_StopTextInput();
}

void textInputRect(const sdl::Rect &rect) {
    // const-casting :'-(
    SDL_SetTextInputRect(const_cast<sdl::Rect *>(&rect));
}

bool hasScreenKeyboardSupport() {
    return SDL_HasScreenKeyboardSupport();
}

bool isScreenKeyboardShown(SDL_Window *window) {
    return SDL_IsScreenKeyboardShown(window);
}

} // namespace sdl
