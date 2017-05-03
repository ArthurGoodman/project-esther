cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

project(esther)

file(GLOB_RECURSE exe_sources "src/esther/*.cpp")
file(GLOB_RECURSE lib_sources "src/libesther/*.cpp" "src/libesther/*.c")
file(GLOB_RECURSE headers "include/*.h")

include_directories("include")

set(EXECUTABLE_OUTPUT_PATH "bin")
set(LIBRARY_OUTPUT_PATH "lib")

add_library(esther SHARED ${lib_sources} ${headers})

add_executable(esther-exe ${exe_sources} ${headers})
set_target_properties(esther-exe PROPERTIES OUTPUT_NAME esther)

target_link_libraries(esther-exe esther)
