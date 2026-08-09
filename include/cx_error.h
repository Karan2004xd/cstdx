#ifndef CX_ERROR_H
#define CX_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "cx_error_layout.h"
#include "cx_error_family.h"
#include "cx_error_category.h"
#include "cx_error_code.h"
#include <stdint.h>

typedef struct cx_error {
  uint32_t family   : CX_ERROR_FAMILY_BITS;
  uint32_t category : CX_ERROR_CATEGORY_BITS;
  uint32_t code     : CX_ERROR_CODE_BITS;
  uint32_t info;
} cx_error_t;

cx_error_t cx_error_create_ok(void);
cx_error_t cx_error_create(uint32_t family, uint32_t category, uint32_t code, uint32_t info);

int cx_error_is_ok(cx_error_t self);
int cx_error_is_bad(cx_error_t self);

uint32_t cx_error_family(cx_error_t self);
uint32_t cx_error_category(cx_error_t self);
uint32_t cx_error_code(cx_error_t self);
uint32_t cx_error_info(cx_error_t self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_H
