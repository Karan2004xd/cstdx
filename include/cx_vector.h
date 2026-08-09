#ifndef CX_VECTOR_H
#define CX_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

typedef struct cx_vector cx_vector_t;
typedef void (*free_callback)(void *);
typedef void (*print_callback)(const void *);

cx_vector_t *cx_vector_create(size_t elem_size);
int cx_vector_free(cx_vector_t *self, free_callback callback);

int cx_vector_push(cx_vector_t *self, const void *value);
int cx_vector_fill(const cx_vector_t *self, void *dst, size_t index);
const void *cx_vector_get(const cx_vector_t *self, size_t index);

int cx_vector_set(cx_vector_t *self, const void *value, size_t index);
int cx_vector_pop(cx_vector_t *self, size_t index, free_callback callback);
int cx_vector_clear(cx_vector_t *self, free_callback callback);

int cx_vector_shrink_to_fit(cx_vector_t *self);
int cx_vector_resize(cx_vector_t *self, size_t new_size, free_callback callback);
int cx_vector_reserve(cx_vector_t *self, size_t new_capacity);

void cx_vector_capacity(const cx_vector_t *self, size_t *dst);
void cx_vector_size(const cx_vector_t *self, size_t *dst);
int cx_vector_print(const cx_vector_t *self, print_callback callback);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_VECTOR_H
