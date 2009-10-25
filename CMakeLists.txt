cmake_minimum_required(VERSION 2.6)

project(GameboyEmulator)
set(CMAKE_CXX_FLAGS "-g -Wall")

add_library(gz80 cpu/gz80.cc)
add_library(memory mem/bus.cc mem/rom.cc mem/ram.cc)

add_executable(emu main.cc)

target_link_libraries(emu gz80 memory)
