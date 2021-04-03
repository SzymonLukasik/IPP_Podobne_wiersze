#include <stdlib.h>

#include "safealloc.h"
#include "vector.h"

vector new_vector(void) {
  vector v;
  v.data = NULL;
  v.size = 0;
  v.capacity = 0;
  return v;
}

void vector_add(vector* v, void* item) {
  if (v->size == v->capacity) {
    if (v->capacity == 0)
      v->capacity = 1;
    else
      v->capacity *= 2;
    v->data = (void**)safe_realloc(v->data, v->capacity * (sizeof(void*)));
  }
  v->data[v->size] = item;
  v->size++;
}

void vector_delete(vector v) {
  for (size_t i = 0; i < v.size; i++)
    free(v.data[i]);
  free(v.data);
}