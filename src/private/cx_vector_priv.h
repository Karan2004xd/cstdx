#ifndef CX_VECTOR_PRIV_H
#define CX_VECTOR_PRIV_H

#ifndef CX_VECTOR_PRIVATE_ACCESS
#error "Error: This is an internal header and not to be made public."
#endif // CX_VECTOR_PRIVATE_ACCESS

#define DEFAULT_CAPACITY 10
#define DEFAULT_EXPAND_FACTOR 2
#define DEFAULT_SHRINK_THRESHOLD 4
#define DEFAULT_SHRINK_FACTOR 2

#include <stddef.h>

typedef struct cx_vector {
  void *data;
  size_t elem_size;
  size_t size;
  size_t capacity;
} cx_vector_t;

#endif // CX_VECTOR_PRIV_H
