project(src)

add_library(${PROJECT_NAME}
  "./cx_error.c"
)

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE TESTING)
