cmake_minimum_required(VERSION 3.26)
project(cstdx)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wconversion -Wsign-conversion -Wall -Wextra -Wpedantic -Werror")

add_subdirectory("./src")
add_subdirectory("./tests")
