project(tests)
include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/doctest/doctest.git"
  GIT_TAG "v2.5.3"
)
FetchContent_MakeAvailable(doctest)

set(TEST_SOURCES
  "./cx_error_test.cpp"
)
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
  TESTING
  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE src doctest
)
