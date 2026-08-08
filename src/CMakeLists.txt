project(src)

add_library(${PROJECT_NAME}
  "cx_vector.c"
)

target_include_directories(
  ${PROJECT_NAME}
    PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  CX_VECTOR_PRIVATE_ACCESS
  TESTING
)
