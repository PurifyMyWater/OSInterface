cmake_minimum_required(VERSION 3.16)

Project(OSInterface)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(OSInterface INTERFACE)
target_include_directories(OSInterface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
