cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary system packages
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

# Collect source files (adjust if you add more .cpp files in src/)
file(GLOB SOURCES "src/*.cpp")

# Define the executable target
add_executable(cloud_controller ${SOURCES})

# Tell CMake and VS Code where to find header files
target_include_directories(cloud_controller PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

# Link required libraries (ALSA for MIDI/Audio, SDL2 for window/input, Threads)
target_link_libraries(cloud_controller PRIVATE
    ${SDL2_LIBRARIES}
    asound
    Threads::Threads
)