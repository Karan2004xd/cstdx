#include <doctest/doctest.h>
#include "../include/cx_error.h"

TEST_CASE("cx_error_create") {
  cx_error_t err = cx_error_create(CX_ERROR_FAMILY_CONTAINERS, CX_ERROR_CATEGORY_VECTOR, CX_ERROR_CATEGORY, uint32_t info)
}
