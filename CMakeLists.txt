cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find system libraries (SDL2, Threads)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(cloud_controller ${SOURCES})

# Explicitly use absolute path to include directory so the compiler finds nlohmann/json.hpp
target_include_directories(cloud_controller PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(cloud_controller PRIVATE
    ${SDL2_LIBRARIES}
    SDL2_ttf::SDL2_ttf
    asound
    Threads::Threads
)