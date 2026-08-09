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
  return self.family;
}

uint32_t cx_error_code(cx_error_t self) {
  return self.code;
}

uint32_t cx_error_info(cx_error_t self) {
  return self.info;
}

static cx_error_t create_error_(
    uint32_t family, uint32_t category,
    uint32_t code, uint32_t info) {
  return (cx_error_t) {
    .family = family, .category = category, .code = code, .info = info,
  };
}
