cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_X_FLAGS} -Wall -pedantic")

project(esther)

file(GLOB_RECURSE exe_sources "src/esther/*.cpp")
file(GLOB_RECURSE lib_sources "src/libesther/*.cpp" "src/libesther/*.c")
file(GLOB_RECURSE headers "include/*.h")

include_directories("include")

set(EXECUTABLE_OUTPUT_PATH "bin")
set(LIBRARY_OUTPUT_PATH "lib")

add_library(libesther SHARED ${lib_sources} ${headers})
set_target_properties(libesther PROPERTIES OUTPUT_NAME esther)

add_executable(esther ${exe_sources} ${headers})

target_link_libraries(esther libesther)
