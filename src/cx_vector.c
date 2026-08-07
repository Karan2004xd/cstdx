#define CX_VECTOR_PRIVATE_ACCESS
#include "./private/cx_vector_priv.h"
#include "../include/cx_vector.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static int check_positive_(long value);
static int set_value_(cx_vector_t *self, void *value, long index);

cx_vector_t *cx_vector_create(long elem_size) {
  if (elem_size <= 0) {
    fprintf(stderr, "cx_vector: elem_size must be positive. Provided (elem_size=%ld)\n", elem_size);
  }

  cx_vector_t *vec = (cx_vector_t *) malloc(sizeof(cx_vector_t));

  if (!vec) {
    fprintf(stderr, "cx_vector: unable to create.\n");
    return NULL;
  }

  vec->capacity = DEFAULT_CAPACITY;
  vec->elem_size = elem_size;
  vec->size = 0;
  vec->data = (void *) malloc(vec->elem_size * vec->capacity);

  if (!vec->data) {
    fprintf(stderr, "cx_vector: unable to allocate space.\n");
    free(vec);
    return NULL;
  }
  return vec;
}

void cx_vector_free(cx_vector_t *self, free_callback callback) {
  if (!self) return ;

  if (self->data) {
    if (callback) callback(self->data);
    else free(self->data);
  }

  self->data = NULL;
  self->capacity = 0;
  self->size = 0;
  free(self);
}

void cx_vector_push(cx_vector_t *self, void *value) {
  if (self->size >= self->capacity - 1) {
    // expand
  }
}

void cx_vector_fill(const cx_vector_t *self, void *dst, long index);
void *cx_vector_get(const cx_vector_t *self, long index);
