cmake_minimum_required(VERSION 2.8)

project(esther)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(esther)
add_subdirectory(testher)
