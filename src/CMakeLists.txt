project(src)

add_library(${PROJECT_NAME}
  "./cx_error.h"
)

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
)
