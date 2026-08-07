#define CX_VECTOR_PRIVATE_ACCESS
#include <doctest/doctest.h>

#include "../src/private/cx_vector_priv.h"
#include "../include/cx_vector.h"

TEST_CASE("cx_vector create") {
  cx_vector_t *vec = cx_vector_create(100);
  cx_vector_free(vec, NULL);
}
