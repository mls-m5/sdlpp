Lasersköld sdlpp
================

Basic c++ wrapper around sdl2's c api

## Example

```c++
#include "sdlpp/render.hpp"
#include "sdlpp/window.hpp"
#include <thread>

int main(int argc, char **argv) {
    auto window = sdl::Window{"sdl window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              500,
                              500,
                              SDL_WINDOW_OPENGL};

    auto renderer = sdl::Renderer{window.get(), -1, SDL_RENDERER_ACCELERATED};

    if (!renderer) {
        std::cerr << "could not create renderer\n";
        return 1;
    }

    renderer.drawColor({100, 0, 0, 255});
    renderer.clear();
    renderer.drawColor({100, 100, 100, 255});
    renderer.drawLine(0, 0, 100, 100);
    renderer.present();

    std::this_thread::sleep_for(1000ms);

    return 0;
}
``` 
