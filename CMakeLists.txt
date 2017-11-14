cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++11)
include_directories("${CMAKE_SOURCE_DIR}/inc")
add_subdirectory(src)
add_subdirectory(examples)

