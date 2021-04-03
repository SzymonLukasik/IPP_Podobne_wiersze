#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector {
  void** data; /* Tablica wskażników na elementy znajdujące się w wektorze */
  size_t size; /* Ilość obecnie znajdujących się w wektorze elementów */
  size_t capacity; /* Ilość elementów dla których została zalokowana pamięć */
} vector;

/* Funkcja zwracająca pusty wektor */
vector new_vector(void);

/* Funkcja dodająca element do wektora */
void vector_add(vector* v, void* item);

/* Funkcja zwalniająca pamięć zalokowaną przez wektor */
void vector_delete(vector v);

#endif /* VECTOR_H */