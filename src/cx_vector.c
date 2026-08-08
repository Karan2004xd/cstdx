#include "./private/cx_vector_priv.h"
#include "../include/cx_vector.h"
#include "../include/macros.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int check_positive_(long value, int allow_zero);
static int check_index_(const cx_vector_t *self, long index);
static void set_value_(cx_vector_t *self, const void *value, long index);
static int expand_vector_(cx_vector_t *self);
static void *get_index_ptr_(const cx_vector_t *self, long index);

cx_vector_t *cx_vector_create(long elem_size) {
  if (check_positive_(elem_size, 0) == -1) {
    LOG_ERROR("elem_size must be positive. Provided (elem_size = %ld)", elem_size);
    return NULL;
  }

  cx_vector_t *vec = (cx_vector_t *) malloc(sizeof(cx_vector_t));

  if (!vec) {
    LOG_ERROR("unable to create.");
    return NULL;
  }

  vec->capacity = DEFAULT_CAPACITY;
  vec->elem_size = elem_size;
  vec->size = 0;
  vec->data = (void *) malloc(vec->elem_size * vec->capacity);

  if (!vec->data) {
    LOG_ERROR("unable to allocate space.");
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

int cx_vector_push(cx_vector_t *self, const void *value) {
  if (self->size >= self->capacity - 1) {
    int res = expand_vector_(self);
    if (res == -1) LOG_ERROR("Unable to expand.");
    if (res == 1) LOG_ERROR("Ran out of space.");
    if (res != 0) return -1;
  }

  set_value_(self, value, self->size);
  self->size++;
  return 0;
}

int cx_vector_fill(const cx_vector_t *self, void *dst, long index) {
  const void *src = get_index_ptr_(self, index);
  if (!src) return -1;
  memcpy(dst, src, self->elem_size);
  return 0;
}

int cx_vector_set(cx_vector_t *self, const void *value, long index) {
  return set_value_(self, value, index);
}

const void *cx_vector_get(const cx_vector_t *self, long index) {
  return get_index_ptr_(self, index);
}

static int check_positive_(long value, int allow_zero) {
  return (value < 0 || (value == 0 && !allow_zero)) ? -1 : 0;
}

static int check_index_(const cx_vector_t *self, long index) {
  if (index < 0 || (size_t) index >= self->size) {
    LOG_ERROR("Index (%ld) out of bounds.", index);
    return -1;
  }
  return 0;
}

static void set_value_(cx_vector_t *self, const void *value, long index) {
  void *dst = get_index_ptr_(self, index);
  if (!dst) {
    LOG_WARN("Unable to set value at index (%ld)", index);
    return ;
  }
  memcpy(dst, value, self->elem_size);
}

static int expand_vector_(cx_vector_t *self) {
  size_t new_capacity = self->capacity * DEFAULT_EXPAND_FACTOR;

  if (new_capacity >= MAX_CAPACITY(self->elem_size)) {
    return 1;
  }

  void *temp = realloc(self->data, new_capacity * self->elem_size);
  if (!temp) return -1;

  self->data = temp;
  self->capacity = new_capacity;
  return 0;
}

static void *get_index_ptr_(const cx_vector_t *self, long index) {
  if (check_index_(self, index) == -1) {
    return NULL;
  }
  return (char *) self->data + (index * self->elem_size);
}
