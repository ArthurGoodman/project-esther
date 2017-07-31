cmake_minimum_required(VERSION 2.8)

project(esther)

file(GLOB_RECURSE esther_sources "src/esther/*.cpp")
file(GLOB_RECURSE libesther_sources "src/libesther/*.cpp" "src/libesther/*.c")
file(GLOB_RECURSE libesther_headers "include/*.h" "src/libesther/*.h")
file(GLOB_RECURSE libio_sources "src/io/*.cpp" "src/io/*.c")

include_directories("include")

set(EXECUTABLE_OUTPUT_PATH "bin")
set(LIBRARY_OUTPUT_PATH "lib")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(FLAGS "-Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_X_FLAGS} ${FLAGS}")

add_library(libesther SHARED ${libesther_sources} ${libesther_headers})
set_target_properties(libesther PROPERTIES OUTPUT_NAME esther)

if(UNIX)
target_link_libraries(libesther dl)
endif()

if(WIN32)
add_definitions(-D__USE_MINGW_ANSI_STDIO=1)

add_custom_command(
    TARGET libesther
    COMMAND dlltool -l lib/libesther.lib --export-all-symbol lib/libesther.dll)
endif()

add_library(libio SHARED ${libio_sources})
set_target_properties(libio PROPERTIES OUTPUT_NAME io)
target_link_libraries(libio libesther)

add_executable(esther ${esther_sources})
target_link_libraries(esther libesther)
