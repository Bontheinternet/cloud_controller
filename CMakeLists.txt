cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find system libraries
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

# Collect source files
file(GLOB SOURCES "src/*.cpp")

# Define executable target
add_executable(cloud_controller ${SOURCES})

# Use absolute path to guarantee the compiler finds the local include folder
target_include_directories(cloud_controller PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Link required libraries
target_link_libraries(cloud_controller PRIVATE
    ${SDL2_LIBRARIES}
    asound
    Threads::Threads
)