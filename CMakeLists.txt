
cmake_minimum_required(VERSION 3.16)
project(sdlpp)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    )


target_compile_features(
    ${PROJECT_NAME}
    INTERFACE
    cxx_std_20
    )

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    include
    )

if (EMSCRIPTEN)
    target_compile_options(
        ${PROJECT_NAME}
        INTERFACE
        -sUSE_SDL=2
        -sUSE_SDL_IMAGE=2
    )

    target_link_options(
        ${PROJECT_NAME}
        INTERFACE
        -sUSE_SDL=2
        -sUSE_SDL_IMAGE=2
    )
else()

    find_package(SDL2 REQUIRED)


    target_link_libraries(
        ${PROJECT_NAME}
        INTERFACE
        ${SDL2_LIBRARIES}
        )

    target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        ${SDL2_INCLUDE_DIRS}
        )

endif()
