#include <doctest/doctest.h>

#include "../src/private/cx_vector_priv.h"
#include "../include/cx_vector.h"

TEST_CASE("cx_vector create") {
  cx_vector_t *vec = cx_vector_create(sizeof(int));
  REQUIRE(vec != NULL);
  CHECK(vec->elem_size == sizeof(int));
  CHECK(vec->capacity == DEFAULT_CAPACITY);
  CHECK(vec->size == 0);

  int val;
  CHECK(cx_vector_fill(vec, &val, 0) == -1);

  for (int i = 1; i <= 5; i++) {
    REQUIRE(cx_vector_push(vec, &i) != -1);
    REQUIRE(cx_vector_fill(vec, &val, i - 1) != -1);
    REQUIRE(cx_vector_get(vec, i - 1) != nullptr);
    CHECK(*(const int *) cx_vector_get(vec, i - 1) == i);
    CHECK(val == i);
  }
  cx_vector_free(vec, NULL);
}
