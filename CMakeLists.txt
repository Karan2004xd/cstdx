cmake_minimum_required(VERSION 3.26)
project(cstdx)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Werror")

add_executable(${PROJECT_NAME} "main.c")

add_subdirectory("./src")
add_subdirectory("./tests")

target_link_libraries(${PROJECT_NAME} PRIVATE src)
