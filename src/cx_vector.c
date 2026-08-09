#include "./private/cx_vector_priv.h"
#include "../include/cx_vector.h"
#include "../include/macros.h"

#include <stdlib.h>
#include <string.h>

static int check_index_(const cx_vector_t *self, size_t index);
static int set_value_(cx_vector_t *self, const void *value, size_t index);
static int expand_vector_(cx_vector_t *self, unsigned expand_factor);
static void *get_index_ptr_(const cx_vector_t *self, size_t index);
static int try_to_shrink_(cx_vector_t *self, int to_fit);
static int try_to_expand_(cx_vector_t *self, unsigned expand_factor);
static int expand_vector_to_(cx_vector_t *self, size_t capacity);
static int pass_elem_to_callback_(cx_vector_t *self, size_t from, size_t to, free_callback callback);
static int check_self_(const cx_vector_t *self, int as_error);
static int overflow_safe_umul_(size_t x, size_t y, size_t *result);

cx_vector_t *cx_vector_create(size_t elem_size) {
  cx_vector_t *vec = (cx_vector_t *) malloc(sizeof(cx_vector_t));

  if (!vec) {
    LOG_ERROR("unable to create.");
    return NULL;
  }

  vec->capacity = DEFAULT_CAPACITY;
  vec->elem_size = elem_size;
  vec->size = 0;

  size_t total_data_size;
  if (overflow_safe_umul_(vec->elem_size, vec->capacity, &total_data_size)) {
    free(vec);
    return NULL;
  }

  vec->data = (void *) malloc(total_data_size);

  if (!vec->data) {
    LOG_ERROR("unable to allocate space.");
    free(vec);
    return NULL;
  }
  return vec;
}

int cx_vector_free(cx_vector_t *self, free_callback callback) {
  if (check_self_(self, 0) == -1) return 0;

  if (self->data) {
    if (pass_elem_to_callback_(self, 0, self->size, callback) == -1) {
      return -1;
    }
    free(self->data);
  }

  self->data = NULL;
  self->capacity = 0;
  self->size = 0;
  free(self);
  return 0;
}

int cx_vector_push(cx_vector_t *self, const void *value) {
  if (check_self_(self, 1) == -1) return -1;
  if (try_to_expand_(self, DEFAULT_EXPAND_FACTOR) == -1) return -1;

  self->size++;
  if (set_value_(self, value, self->size - 1) == -1) {
    self->size--;
    return -1;
  }
  return 0;
}

int cx_vector_fill(const cx_vector_t *self, void *dst, size_t index) {
  if (check_self_(self, 1) == -1) return -1;

  const void *src = get_index_ptr_(self, index);
  if (!src) return -1;
  memcpy(dst, src, self->elem_size);
  return 0;
}

int cx_vector_set(cx_vector_t *self, const void *value, size_t index) {
  if (check_self_(self, 1) == -1) return -1;
  return set_value_(self, value, index);
}

const void *cx_vector_get(const cx_vector_t *self, size_t index) {
  if (check_self_(self, 1) == -1) return NULL;
  return get_index_ptr_(self, index);
}

int cx_vector_pop(cx_vector_t *self, size_t index, free_callback callback) {
  if (check_self_(self, 1) == -1) return -1;
  if (check_index_(self, index) == -1) return -1;

  void *dst = get_index_ptr_(self, index);
  if (!dst) return -1;

  if (callback) callback(dst);

  if (index < self->size - 1) {
    const void *src;

    if ((src = get_index_ptr_(self, index + 1)) == NULL) return -1;

    if (callback) callback(dst);
    size_t bytes_to_move = self->elem_size * (self->size - index - 1);
    memmove(dst, src, bytes_to_move);
  }
  self->size--;
  try_to_shrink_(self, 0);
  return 0;
}

int cx_vector_clear(cx_vector_t *self, free_callback callback) {
  if (check_self_(self, 1) == -1) return -1;
  if (pass_elem_to_callback_(self, 0, self->size, callback) == -1) return -1;

  self->size = 0;
  try_to_shrink_(self, 0);
  return 0;
}

int cx_vector_shrink_to_fit(cx_vector_t *self) {
  if (check_self_(self, 1) == -1) return -1;
  return try_to_shrink_(self, 1);
}

int cx_vector_resize(cx_vector_t *self, size_t new_size, free_callback callback) {
  if (check_self_(self, 1) == -1) return -1;

  size_t old_size = self->size;
  if (new_size == old_size) {
    return 0;
  }

  if (new_size < old_size) {
    if (pass_elem_to_callback_(self, new_size, self->size, callback) == -1) {
      return -1;
    }

    self->size = new_size;
    try_to_shrink_(self, 0);

  } else {
    if (expand_vector_to_(self, new_size) == -1) {
      return -1;
    }
    self->size = new_size;

    void *new_elem_ptr = get_index_ptr_(self, old_size);
    if (!new_elem_ptr) return -1;

    size_t new_elements = new_size - old_size;
    memset(new_elem_ptr, 0, new_elements * self->elem_size);
  }
  return 0;
}

int cx_vector_reserve(cx_vector_t *self, size_t new_capacity) {
  if (check_self_(self, 1) == -1) return -1;
  return expand_vector_to_(self, new_capacity);
}

void cx_vector_capacity(const cx_vector_t *self, size_t *dst) {
  if (check_self_(self, 0) == -1) return ;
  *dst = self->capacity;
}

void cx_vector_size(const cx_vector_t *self, size_t *dst) {
  if (check_self_(self, 0) == -1) return ;
  *dst = self->size;
}

int cx_vector_print(const cx_vector_t *self, print_callback callback) {
  if (check_self_(self, 0) == -1) return -1;
  if (!callback) return 1;

  for (size_t i = 0; i < self->size; i++) {
    void *elem = get_index_ptr_(self, i);
    if (!elem) return -1;
    callback(elem);
  }
  return 0;
}

static int check_index_(const cx_vector_t *self, size_t index) {
  if (index >= self->size) {
    LOG_ERROR("Index (%ld) out of bounds.", index);
    return -1;
  }
  return 0;
}

static int set_value_(cx_vector_t *self, const void *value, size_t index) {
  void *dst = get_index_ptr_(self, index);
  if (!dst) {
    LOG_WARN("Unable to set value at index (%ld)", index);
    return -1;
  }
  memcpy(dst, value, self->elem_size);
  return 0;
}

static int expand_vector_(cx_vector_t *self, unsigned expand_factor) {
  if (expand_factor == 0) return -1;

  size_t new_capacity;
  if (overflow_safe_umul_(self->capacity, expand_factor, &new_capacity)) {
    return -1;
  }

  if (new_capacity >= MAX_CAPACITY(self->elem_size)) {
    return 1;
  }

  size_t total_capacity;
  if (overflow_safe_umul_(new_capacity, self->elem_size, &total_capacity)) {
    return -1;
  }

  void *temp = realloc(self->data, MAX(total_capacity, self->elem_size));
  if (!temp) return -1;

  self->data = temp;
  self->capacity = new_capacity;
  return 0;
}

static void *get_index_ptr_(const cx_vector_t *self, size_t index) {
  if (check_index_(self, index) == -1) {
    return NULL;
  }
  return (uint8_t *) self->data + (index * self->elem_size);
}

static int try_to_shrink_(cx_vector_t *self, int to_fit) {
  size_t new_capacity = self->size;

  if (!to_fit) {
    size_t cap_in_use = self->capacity / DEFAULT_SHRINK_THRESHOLD;

    if (self->size >= cap_in_use || self->capacity <= DEFAULT_CAPACITY) {
      LOG_INFO("No shrink needed yet!");
      return 1;
    }
    new_capacity = self->capacity / DEFAULT_SHRINK_FACTOR;
  }

  size_t total_capacity;
  if (overflow_safe_umul_(new_capacity, self->elem_size, &total_capacity)) {
    return -1;
  }

  void *temp = realloc(self->data, MAX(self->elem_size, total_capacity));
  if (!temp) {
    LOG_WARN("Failed to shrink");
    return -1;
  }

  self->data = temp;
  self->capacity = new_capacity;
  return 0;
}

static int try_to_expand_(cx_vector_t *self, unsigned expand_factor) {
  if (self->capacity == 0 || self->size >= self->capacity - 1) {
    int res = expand_vector_(self, expand_factor);
    if (res == -1) LOG_ERROR("Unable to expand.");
    if (res == 1) LOG_ERROR("Ran out of space.");
    if (res != 0) return -1;
    return 1;
  }
  return 0;
}

static int expand_vector_to_(cx_vector_t *self, size_t capacity) {
  if (capacity <= self->capacity) {
    return 1;
  }

  if (capacity >= MAX_CAPACITY(capacity)) {
    LOG_ERROR("(%ld) capacity greater then max capacity", capacity);
    return -1;
  }

  size_t total_capacity;
  if (overflow_safe_umul_(capacity, self->elem_size, &total_capacity)) {
    return -1;
  }

  void *temp = realloc(self->data, MAX(total_capacity, self->elem_size));
  if (!temp) {
    LOG_ERROR("Failed to expand vector to capacity (%zu)", capacity);
    return -1;
  }

  self->data = temp;
  self->capacity = capacity;
  return 0;
}

static int pass_elem_to_callback_(cx_vector_t *self, size_t from, size_t to, free_callback callback) {
  if (!self) return -1;
  if (!callback) return 0;

  if (from >= to || check_index_(self, to - 1) == -1) {
    return -1;
  }

  while (from < to) {
    void *elem = get_index_ptr_(self, from);
    if (!elem) {
      LOG_ERROR("Element at index (%zu) not found.", from);
      return -1;
    }
    callback(elem);
    from++;
  }
  return 0;
}

static int check_self_(const cx_vector_t *self, int as_error) {
  if (!self) {
    if (as_error) LOG_ERROR("NULL pointer to cx_vector passed");
    else LOG_WARN("NULL pointer to cx_vector passed");
    return -1;
  }
  return 0;
}

static int overflow_safe_umul_(size_t x, size_t y, size_t *result) {
  if (x != 0 && ((x * y) / x) != y) {
    LOG_ERROR("(%zu) * (%zu) overflows size_t", x, y);
    return 1;
  }
  *result = x * y;
  return 0;
}
