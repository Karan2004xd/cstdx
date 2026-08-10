#ifndef CX_ERROR_H
#define CX_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "cx_error_layout.h"
#include "cx_error_family.h"
#include "cx_error_category.h"
#include "cx_error_code.h"

#include <assert.h>
#include <stdint.h>

typedef struct cx_error {
  uint32_t family   : CX_ERROR_FAMILY_BITS;
  uint32_t category : CX_ERROR_CATEGORY_BITS;
  uint32_t code     : CX_ERROR_CODE_BITS;
  uint32_t info;
} cx_error_t;

static_assert(sizeof(cx_error_t) == 8, "The size of error struct must not exceed 8 bytes!");

// Compile time option for creating error, but no assert based bound checks
#define CX_ERROR(fam, cat, cd, inf) \
  ((cx_error_t){ \
    .family   = (uint32_t) (fam & CX_ERROR_FAMILY_MASK), \
    .category = (uint32_t) (cat & CX_ERROR_CATEGORY_MASK), \
    .code     = (uint32_t) (cd & CX_ERROR_CODE_MASK), \
    .info     = inf, \
  })

#define CX_ERROR_OK() \
  ((cx_error_t){ \
    .family   = 0, \
    .category = 0, \
    .code     = 0, \
    .info     = 0, \
  })

#define CX_ERROR_IS_OK(err)   ((err).code == 0)
#define CX_ERROR_IS_BAD(err)  ((err).code != 0)

cx_error_t cx_error_create_ok(void);
cx_error_t cx_error_create(uint32_t family, uint32_t category, uint32_t code, uint32_t info);

int cx_error_is_ok(cx_error_t self);
int cx_error_is_bad(cx_error_t self);

uint32_t cx_error_family(cx_error_t self);
uint32_t cx_error_category(cx_error_t self);
uint32_t cx_error_code(cx_error_t self);
uint32_t cx_error_info(cx_error_t self);

cx_error_t cx_error_with_family(cx_error_t self, uint32_t family);
cx_error_t cx_error_with_category(cx_error_t self, uint32_t category);
cx_error_t cx_error_with_code(cx_error_t self, uint32_t code);
cx_error_t cx_error_with_info(cx_error_t self, uint32_t info);
cx_error_t cx_error_with_error(cx_error_t src);

int cx_error_is_equal(cx_error_t lhs, cx_error_t rhs);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_H
