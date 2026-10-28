cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json.hpp")
if(NOT EXISTS "${JSON_HEADER}")
    message(STATUS "Downloading nlohmann/json.hpp for build environment...")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/nlohmann/json/v3.11.3/single_include/nlohmann/json.hpp"
        "${JSON_HEADER}"
        STATUS download_status
    )
    list(GET download_status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download nlohmann/json.hpp during configuration!")
    endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(cloud_controller ${SOURCES})

target_include_directories(cloud_controller PRIVATE
    ${CMAKE_CURRENT_S    ${CMAKE_CURRENT_S    ${C2_    ${CMAKE_CURRENT_S    ${CMAKE_CUies(cloud_controller PRIVATE
                          SDL2_ttf::SDL2_ttf
    asound
    Threads:    Threads:    Threads:    Threads:    Threads:    Threads:    Threnlohmann json header during CMake configure step"
git push origin main

cat << 'EOF' > CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(cloud_controller CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json.hpp")
if(NOT EXISTS "${JSON_HEADER}")
    message(STATUS "Downloading nlohmann/json.hpp for build environment...")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/nlohmann/json/v3.11.3/single_include/nlohmann/json.hpp"
        "${JSON_HEADER}"
        STATUS download_status
    )
    list(GET download_status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download nlohmann/json.hpp during configuration!")
    endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(cloud_controller ${SOURCES})

target_include_directories(cloud_controller PRIVATE
    ${CMAKE_CURRENT_S    ${CMAKE_CURRENT_S    ${C2_    ${CMAKE_CURRENT_S    ${CMAKbrarie    ${CMAKE_CURRENT_SIVATE
    ${SDL2_LIBRARIES}
    SDL2_    SDL2_    SDL2_    SDL2_    SDLds::Threads
)
