#ifndef CX_VECTOR_H
#define CX_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cx_vector cx_vector_t;
typedef void (*free_callback)(void *);

cx_vector_t *cx_vector_create(long elem_size);
void cx_vector_free(cx_vector_t *self, free_callback callback);

int cx_vector_push(cx_vector_t *self, const void *value);
int cx_vector_fill(const cx_vector_t *self, void *dst, long index);
const void *cx_vector_get(const cx_vector_t *self, long index);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CX_VECTOR_H
