
cmake_minimum_required(VERSION 3.23)
project(sdlpp)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    )

list(APPEND
    CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    include
    ${SDL2_INCLUDE_DIRS}
    )

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    SDL2::Main
    )

target_compile_features(
    ${PROJECT_NAME}
    INTERFACE
    cxx_std_17
    )
