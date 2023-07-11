
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
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -sUSE_SDL=2"
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
