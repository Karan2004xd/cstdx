#ifndef CX_ERROR_LAYOUT_H
#define CX_ERROR_LAYOUT_H

/**
* LAYOUT : 32-bits (error) + 32-bits (info) = 64-bits (8 bytes)
* error 32-bits breakdown:
*   6-bits  -> 64 error families.
*   10-bits -> 1024 error category, per family.
*   16-bits -> 65,536 error codes, per category.
**/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define CX_ERROR_FAMILY_BITS    6u
#define CX_ERROR_CATEGORY_BITS  10u
#define CX_ERROR_CODE_BITS      16u
#define CX_ERROR_INFO_BITS      32u

#define CX_ERROR_FAMILY_MASK    ((1u << CX_ERROR_FAMILY_BITS) - 1u)
#define CX_ERROR_CATEGORY_MASK  ((1u << CX_ERROR_CATEGORY_BITS) - 1u)
#define CX_ERROR_CODE_MASK      ((1u << CX_ERROR_CODE_BITS) - 1u)
#define CX_ERROR_INFO_MASK      0xFFFFFFFFu    

#define CX_ERROR_FAMILY_SHIFT   (CX_ERROR_CATEGORY_BITS + CX_ERROR_CODE_BITS + CX_ERROR_INFO_BITS)
#define CX_ERROR_CATEGORY_SHIFT (CX_ERROR_CODE_BITS + CX_ERROR_INFO_BITS)
#define CX_ERROR_CODE_SHIFT     (CX_ERROR_INFO_BITS)
#define CX_ERROR_INFO_SHIFT     0u

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_ERROR_LAYOUT_H
