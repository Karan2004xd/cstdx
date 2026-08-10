#include "../include/cx_error.h"

static cx_error_t create_error_(
    uint32_t family, uint32_t category,
    uint32_t code, uint32_t info);

cx_error_t cx_error_create_ok(void) {
  return create_error_(0, 0, 0, 0);
}

cx_error_t cx_error_create(
    uint32_t family, uint32_t category,
    uint32_t code, uint32_t info) {
  return create_error_(family, category, code, info);
}

int cx_error_is_ok(cx_error_t self) {
  return self.code == 0;
}

int cx_error_is_bad(cx_error_t self) {
  return self.code != 0;
}

uint32_t cx_error_family(cx_error_t self) {
  return self.family;
}

uint32_t cx_error_category(cx_error_t self) {
  return self.category;
}

uint32_t cx_error_code(cx_error_t self) {
  return self.code;
}

uint32_t cx_error_info(cx_error_t self) {
  return self.info;
}

cx_error_t cx_error_with_family(cx_error_t self, uint32_t family) {
  return create_error_(family, self.category, self.code, self.info);
}

cx_error_t cx_error_with_category(cx_error_t self, uint32_t category) {
  return create_error_(self.family, category, self.code, self.info);
}

cx_error_t cx_error_with_code(cx_error_t self, uint32_t code) {
  return create_error_(self.family, self.category, code, self.info);
}

cx_error_t cx_error_with_info(cx_error_t self, uint32_t info) {
  return create_error_(self.family, self.category, self.code, info);
}

cx_error_t cx_error_with_error(cx_error_t src) {
  return create_error_(src.family, src.category, src.code, src.info);
}

int cx_error_is_equal(cx_error_t lhs, cx_error_t rhs) {
  if (lhs.family != rhs.family) return 0;
  if (lhs.category != rhs.category) return 0;
  if (lhs.code != rhs.code) return 0;
  if (lhs.info != rhs.info) return 0;
  return 1;
}

static cx_error_t create_error_(
    uint32_t family, uint32_t category,
    uint32_t code, uint32_t info) {

  assert((family & ~CX_ERROR_FAMILY_MASK) == 0 && "family exceeds the bitfield limit!");
  assert((category & ~CX_ERROR_CATEGORY_MASK) == 0 && "category exceeds the bitfield limit!");
  assert((code & ~CX_ERROR_CODE_MASK) == 0 && "code exceeds the bitfield limit!");

  return (cx_error_t) {
    .family   = (uint32_t) (family & CX_ERROR_FAMILY_MASK),
    .category = (uint32_t) (category & CX_ERROR_CATEGORY_MASK),
    .code     = (uint32_t) (code & CX_ERROR_CODE_MASK),
    .info     = info,
  };
}
