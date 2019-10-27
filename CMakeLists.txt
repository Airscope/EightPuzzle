cmake_minimum_required(VERSION 3.14)
project(eightpuzzle)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-O3 -Wall -Wno-sign-compare)

aux_source_directory(src SRC_DIR)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(eightpuzzle ${SRC_DIR})
