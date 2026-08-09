#ifndef CX_ERROR_CODE_H
#define CX_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef TESTING
// Test error codes 
typedef enum cx_test_code {
  CX_ERROR_CODE_TEST_NONE        = 0x000,
  CX_ERROR_CODE_TEST_VOID        = 0x001,
  CX_ERROR_CODE_TEST_MAX         = 0x3FF    // 10-bits
} cx_test_code_t;
#endif // TESTING

// cx_vector error codes
typedef enum cx_vector_code {
  CX_ERROR_CODE_VEC_OK          = 0x0000,

  CX_ERROR_CODE_VEC_MAX         = 0xFFFF    // 10-bits
} cx_vector_code_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_CODE_H
