#ifndef CX_ERROR_CATEGORY_H
#define CX_ERROR_CATEGORY_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef TESTING
// Test Category
typedef enum cx_test_category {
  CX_ERROR_CATEGORY_TEST_NONE        = 0x000,
  CX_ERROR_CATEGORY_TEST_VOID        = 0x001,
  CX_ERROR_CATEGORY_TEST_MAX         = 0x3FF    // 10-bits
} cx_test_category_t;
#endif // TESTING

// Container Category
typedef enum cx_cont_category {
  CX_ERROR_CATEGORY_NONE        = 0x000,

  CX_ERROR_CATEGORY_VECTOR      = 0x001,
  CX_ERROR_CATEGORY_STACK       = 0x002,
  CX_ERROR_CATEGORY_QUEUE       = 0x003,
  CX_ERROR_CATEGORY_HASHMAP     = 0x004,

  CX_ERROR_CATEGORY_MAX         = 0x3FF    // 10-bits
} cx_cont_category_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_CATEGORY_H
