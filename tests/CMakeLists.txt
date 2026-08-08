project(tests)
include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/doctest/doctest.git"
  GIT_TAG "v2.5.3"
)
FetchContent_MakeAvailable(doctest)

set(TEST_SOURCES
  "cx_vector_test.cpp"
)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
  TESTING
  CX_VECTOR_PRIVATE_ACCESS
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE src doctest
)
