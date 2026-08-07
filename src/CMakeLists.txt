project(src)

add_library(${PROJECT_NAME}
  "cx_vector.c"
)

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
)
