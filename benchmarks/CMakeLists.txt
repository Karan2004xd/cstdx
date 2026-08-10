project(benchmarks)
include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY "https://github.com/google/benchmark.git"
  GIT_TAG        "v1.9.5"
)
FetchContent_MakeAvailable(googlebenchmark)

set(BENCHMARK_SRCS
  "./cx_error_benchmark.cpp"
)

add_executable(${PROJECT_NAME} ${BENCHMARK_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
  src
  benchmark::benchmark
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  TESTING
)
