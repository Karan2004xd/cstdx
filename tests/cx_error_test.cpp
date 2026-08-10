#include <doctest/doctest.h>
#include "../include/cx_error.h"

TEST_CASE("cx_error: create") {
  cx_error_t err = cx_error_create(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      250 
  );

  CHECK(err.family == CX_ERROR_FAMILY_TEST_VOID);
  CHECK(err.category == CX_ERROR_CATEGORY_TEST_VOID);
  CHECK(err.code == CX_ERROR_CODE_TEST_VOID);
  CHECK(err.info == 250);

  cx_error_t ok_err = cx_error_create_ok();
  CHECK(ok_err.family == 0);
  CHECK(ok_err.category == 0);
  CHECK(ok_err.code == 0);
  CHECK(ok_err.info == 0);

  cx_error_t st_err = CX_ERROR(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      250
  );

  CHECK(st_err.family == CX_ERROR_FAMILY_TEST_VOID);
  CHECK(st_err.category == CX_ERROR_CATEGORY_TEST_VOID);
  CHECK(st_err.code == CX_ERROR_CODE_TEST_VOID);
  CHECK(st_err.info == 250);
}

TEST_CASE("cx_error: getters") {
  cx_error_t bad_err = cx_error_create(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      250 
  );
  cx_error_t ok_err = cx_error_create_ok();

  CHECK(cx_error_is_ok(ok_err) == 1);
  CHECK(cx_error_is_bad(bad_err) == 1);
  CHECK(CX_ERROR_IS_OK(ok_err) == 1);
  CHECK(CX_ERROR_IS_BAD(bad_err) == 1);

  CHECK(cx_error_is_ok(bad_err) == 0);
  CHECK(cx_error_is_bad(ok_err) == 0);
  CHECK(CX_ERROR_IS_OK(bad_err) == 0);
  CHECK(CX_ERROR_IS_BAD(ok_err) == 0);

  CHECK(cx_error_family(bad_err) == static_cast<uint32_t>(bad_err.family));
  CHECK(cx_error_category(bad_err) == static_cast<uint32_t>(bad_err.category));
  CHECK(cx_error_code(bad_err) == static_cast<uint32_t>(bad_err.code));
  CHECK(cx_error_info(bad_err) == static_cast<uint32_t>(bad_err.info));
}

TEST_CASE("cx_error: checkers") {
  static uint32_t info = 100;
  static cx_error_t lhs = cx_error_create(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      info
  );

  static cx_error_t rhs = cx_error_create(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      info
  );
  int res = 0;

  SUBCASE("are equal") {
    res = 1;
  }

  SUBCASE("are not equal (family diff)") {
    rhs.family = CX_ERROR_FAMILY_TEST_NONE;
  }

  SUBCASE("are not equal (category diff)") {
    rhs.category = CX_ERROR_CATEGORY_TEST_NONE;
  }

  SUBCASE("are not equal (code diff)") {
    rhs.code = CX_ERROR_CODE_TEST_NONE;
  }

  SUBCASE("are not equal (info diff)") {
    rhs.info = info + 1;
  }

  CHECK(cx_error_is_equal(lhs, rhs) == res);
}

TEST_CASE("cx_error: setters") {
  static const cx_error_t err = cx_error_create(
      CX_ERROR_FAMILY_TEST_VOID,
      CX_ERROR_CATEGORY_TEST_VOID,
      CX_ERROR_CODE_TEST_VOID,
      250 
  );
  static cx_error_t err_cp;
  cx_error_t expected = CX_ERROR(err.family, err.category, err.code, err.info);

  SUBCASE("with error") {
    err_cp = cx_error_with_error(err);
  }

  SUBCASE("with family") {
    err_cp = cx_error_with_family(err, CX_ERROR_FAMILY_TEST_NONE);
    expected.family = CX_ERROR_FAMILY_TEST_NONE;
  }

  SUBCASE("with category") {
    err_cp = cx_error_with_category(err, CX_ERROR_CATEGORY_TEST_NONE);
    expected.category = CX_ERROR_CATEGORY_TEST_NONE;
  }

  SUBCASE("with code") {
    err_cp = cx_error_with_code(err, CX_ERROR_CODE_TEST_NONE);
    expected.code = CX_ERROR_CODE_TEST_NONE;
  }

  SUBCASE("with info") {
    err_cp = cx_error_with_info(err, err.info + 1);
    expected.info = err.info + 1;
  }

  CHECK(cx_error_is_equal(err_cp, expected) == 1);
}
