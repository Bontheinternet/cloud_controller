cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Fetch nlohmann/json cleanly via FetchContent FIRST
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# 2. Find system dependencies
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)

# 3. Collect sources
file(GLOB SOURCES "src/*.cpp")

# 4. Define executable target
add_executable(cloud_controller ${SOURCES})

# 5. Explicitly add include directories (including nlohmann's source directory)
target_include_directories(cloud_controller PRIVATE
    include
    ${nlohmann_json_SOURCE_DIR}/single_include
    ${SDL2_INCLUDE_DIRS}
)

# 6. Link libraries and target dependencies
target_link_libraries(cloud_controller PRIVATE
    ${SDL2_LIBRARIES}
    asound
    Threads::Threads
    nlohmann_json::nlohmann_json
)