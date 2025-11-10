cmake_minimum_required(VERSION 3.10)
project(CHIP_8_Emulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp src/chip8.cpp)
add_executable(chip8 ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 ${SDL2_LIBRARIES})
