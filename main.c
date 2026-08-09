#include "include/cx_vector.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct test_obj {
  char *name;
  size_t length;
} test_obj_t;

static test_obj_t *test_obj_create(const char *name) {
  test_obj_t *obj = (test_obj_t *) malloc(sizeof(test_obj_t));
  if (!obj) return NULL;

  obj->name = strdup(name);
  obj->length = strlen(obj->name);
  return obj;
}

static void test_obj_free(void *elem) {
  test_obj_t *ptr = *(test_obj_t **) elem;
  if (!ptr) return ;

  if (ptr->name) {
    free(ptr->name);
  }
  ptr->name = NULL;
  ptr->length = 0;
  free(ptr);
}

static void test_obj_print(const void *elem) {
  const test_obj_t *ptr = *(test_obj_t **) elem;
  if (!ptr) return ;

  printf("\nName: %s\n", ptr->name);
  printf("Length: %zu\n", ptr->length);
}

int main(void) {
  cx_vector_t *vec = cx_vector_create(sizeof(test_obj_t *));
  if (!vec) printf("create failed\n");

  test_obj_t *t = test_obj_create("hello");
  cx_vector_push(vec, &t);

  t = test_obj_create("world");
  cx_vector_push(vec, &t);

  t = test_obj_create("!");
  cx_vector_push(vec, &t);

  cx_vector_print(vec, test_obj_print);

  if (cx_vector_free(vec, test_obj_free) == -1) printf("free failed\n");
  return 0;
}
