project(cstdx_src)

add_library(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
)
