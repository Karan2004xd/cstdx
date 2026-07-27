project(cstdx_tests)
include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/doctest/doctest.git"
  GIT_TAG "v2.5.3"
)
FetchContent_MakeAvailable(doctest)

set(TEST_SOURCES)
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC TESTING)

target_link_libraries(
  ${PROJECT_NAME} src doctest
)
