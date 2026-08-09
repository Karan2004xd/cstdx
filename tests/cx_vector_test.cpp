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

  for (int i = 0; i < DEFAULT_CAPACITY; i++) {
    REQUIRE(cx_vector_push(vec, &i) != -1);
    REQUIRE(cx_vector_fill(vec, &val, i) != -1);
    REQUIRE(cx_vector_get(vec, i) != nullptr);
    CHECK(*(const int *) cx_vector_get(vec, i) == i);
    CHECK(val == i);
  }

  REQUIRE(vec->size == DEFAULT_CAPACITY);
  REQUIRE(cx_vector_pop(vec, 0, NULL) != -1);
  CHECK(*(const int *) cx_vector_get(vec, 0) == 1);

  REQUIRE(cx_vector_resize(vec, 3, NULL) != -1);
  CHECK(vec->size == 3);

  cx_vector_free(vec, NULL);
}

TEST_CASE("cx_vector_create - (fail)") {
  cx_vector_t *vec = cx_vector_create(sizeof(int));
  cx_vector_free(vec, NULL);
}
