cmake_minimum_required(VERSION 3.16)
project(CloudController VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3 -mcpu=cortex-a53 -ftree-vectorize -ffast-math)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(ALSA REQUIRED alsa)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${ALSA_INCLUDE_DIRS}
)

file(GLOB SOURCES src/*.cpp)

add_executable(cloud_controller ${SOURCES})

target_link_libraries(cloud_controller
    PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${ALSA_LIBRARIES}
    pthread
)