#ifndef CX_ERROR_FAMILY_H
#define CX_ERROR_FAMILY_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum cx_family {

#ifdef TESTING
  CX_ERROR_FAMILY_TEST_NONE = 0x00,
  CX_ERROR_FAMILY_TEST_VOID = 0x01,
  CX_ERROR_FAMILY_TEST_MAX = 0x3F,
#endif // TESTING

  CX_ERROR_FAMILY_NONE        = 0x00,

  CX_ERROR_FAMILY_CONTAINERS  = 0x01,
  CX_ERROR_FAMILY_UTILITIES   = 0x02,

  CX_ERROR_FAMILY_MAX         = 0x3F    // 6-bits
} cx_family_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_FAMILY_H
