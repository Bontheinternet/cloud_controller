cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically fetch nlohmann/json header-only library
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(cloud_controller ${SOURCES})

target_include_directories(cloud_controller PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

# Link everything including nlohmann_json target
target_link_libraries(cloud_controller PRIVATE
    ${SDL2_LIBRARIES}
    asound
    Threads::Threads
    nlohmann_json::nlohmann_json
)