#include <stdio.h>

#include "groups.h"
#include "safealloc.h"
#include "vector.h"

vector* new_group() {
  vector* vec = safe_malloc(sizeof(vector));
  *vec = new_vector();
  return vec;
}

/* Funkcja wypisująca numery wierszy należących do grupy. */
static void print_group(vector group) {
  for (size_t i = 0; i < group.size - 1; i++)
    printf("%zd ", *((size_t*)group.data[i]));
  printf("%zd\n", *((size_t*)group.data[group.size - 1]));
}

void print_groups(vector groups) {
  for (size_t i = 0; i < groups.size; i++)
    print_group(*(vector*)groups.data[i]);
}

void groups_delete(vector groups) {
  for (size_t i = 0; i < groups.size; i++)
    vector_delete(*((vector*)groups.data[i]));
  vector_delete(groups);
}