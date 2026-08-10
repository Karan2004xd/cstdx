#include <benchmark/benchmark.h>
#include "../include/cx_error.h"

BENCHMARK_MAIN();

static void BM_cx_error_create_fn_impl(benchmark::State &state) {
  for (auto _ : state) {
    cx_error_t err = cx_error_create(
        CX_ERROR_FAMILY_TEST_NONE,
        CX_ERROR_CATEGORY_TEST_NONE,
        CX_ERROR_CODE_TEST_NONE,
        10
    );
    benchmark::DoNotOptimize(err);
  }
}

static void BM_cx_error_create_macro_impl(benchmark::State &state) {
  for (auto _ : state) {
    cx_error_t err = CX_ERROR(
        CX_ERROR_FAMILY_TEST_NONE,
        CX_ERROR_CATEGORY_TEST_NONE,
        CX_ERROR_CODE_TEST_NONE,
        10
    );
    benchmark::DoNotOptimize(err);
  }
}

static void BM_cx_error_create_ok_fn(benchmark::State &state) {
  for (auto _ : state) {
    cx_error_t err = cx_error_create_ok();
    benchmark::DoNotOptimize(err);
  }
}

static void BM_cx_error_create_ok_macro(benchmark::State &state) {
  for (auto _ : state) {
    cx_error_t err = CX_ERROR_OK();
    benchmark::DoNotOptimize(err);
  }
}

static void BM_cx_error_with_family(benchmark::State &state) {
  cx_error_t err = CX_ERROR_OK();
  uint32_t family = CX_ERROR_FAMILY_TEST_VOID;
  for (auto _ : state) {
    cx_error_t updated = cx_error_with_family(err, family);
    benchmark::DoNotOptimize(updated);
    benchmark::ClobberMemory();
  }
}

static void BM_cx_error_with_category(benchmark::State &state) {
  cx_error_t err = CX_ERROR_OK();
  uint32_t category = CX_ERROR_CATEGORY_TEST_VOID;
  for (auto _ : state) {
    cx_error_t updated = cx_error_with_category(err, category);
    benchmark::DoNotOptimize(updated);
    benchmark::ClobberMemory();
  }
}

static void BM_cx_error_with_code(benchmark::State &state) {
  cx_error_t err = CX_ERROR_OK();
  uint32_t code = CX_ERROR_CODE_TEST_VOID;
  for (auto _ : state) {
    cx_error_t updated = cx_error_with_code(err, code);
    benchmark::DoNotOptimize(updated);
    benchmark::ClobberMemory();
  }
}

static void BM_cx_error_with_info(benchmark::State &state) {
  cx_error_t err = CX_ERROR_OK();
  uint32_t info = 10;
  for (auto _ : state) {
    cx_error_t updated = cx_error_with_info(err, info);
    benchmark::DoNotOptimize(updated);
    benchmark::ClobberMemory();
  }
}

static void BM_cx_error_ok_64u_serializaton_roundtrip(benchmark::State &state) {
  cx_error_t err = CX_ERROR_OK();
  for (auto _ : state) {
    uint64_t raw = cx_error_to_u64(err);
    cx_error_t decoded = cx_error_from_u64(raw);
    benchmark::DoNotOptimize(decoded);
  }
}

static void BM_cx_error_bad_64u_serializaton_roundtrip(benchmark::State &state) {
  cx_error_t err = CX_ERROR(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      10
  );

  for (auto _ : state) {
    uint64_t raw = cx_error_to_u64(err);
    cx_error_t decoded = cx_error_from_u64(raw);
    benchmark::DoNotOptimize(decoded);
  }
}

BENCHMARK(BM_cx_error_create_fn_impl)->Name("BM_cx_error_create_fn");
BENCHMARK(BM_cx_error_create_fn_impl)->Name("BM_cx_error_create_multithreaded_fn")->ThreadRange(1, 8);
BENCHMARK(BM_cx_error_create_macro_impl)->Name("BM_cx_error_create_macro");
BENCHMARK(BM_cx_error_create_macro_impl)->Name("BM_cx_error_create_multithreaded_macro")->ThreadRange(1, 8);

BENCHMARK(BM_cx_error_create_ok_fn);
BENCHMARK(BM_cx_error_create_ok_macro);

BENCHMARK(BM_cx_error_with_family);
BENCHMARK(BM_cx_error_with_category);
BENCHMARK(BM_cx_error_with_code);
BENCHMARK(BM_cx_error_with_info);

BENCHMARK(BM_cx_error_bad_64u_serializaton_roundtrip);
BENCHMARK(BM_cx_error_ok_64u_serializaton_roundtrip);
