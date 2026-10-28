cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(cloud_controller ${SOURCES})

target_include_directories(cloud_controller PRIVATE
    include
    ${nlohmann_json_SOURCE_DIR}/single_include
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(cloud_controller PRIVATE
    nlohmann_json::nlohmann_json
    ${SDL2_LIBRARIES}
    SDL2_ttf::SDL2_ttf
    asound
    Threads::Threads
)
