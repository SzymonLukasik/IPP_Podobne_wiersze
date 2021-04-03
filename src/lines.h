#ifndef LINES_H
#define LINES_H

#include <stdlib.h>
#include "vector.h"

typedef char* string;

/* Definicja typu wyliczeniowego reprezentującego typu liczbowe. */
typedef enum num_type {
  LL,  // long long
  UL,  // unsigned long
  LD,  // long double
} num_type;

/* Definicja uni [num_type] służącej do przechowywania liczb w strukturze
[number] Jeśli liczbę możemy reprezentować jako [long long], robimy to. W
przeciwnym przypadku, jeśli możemy, reprezentujemy ją jako [unsigned long], a
jeśli nie - jako [long double]. */
typedef union num_union {
  long long ll;
  unsigned long ul;
  long double ld;
} num_union;

/* Definicja struktury [number] */
typedef struct number {
  num_union val;  // Wartość liczby
  num_type type;  // Aktualny typ liczby
} number;

/* Definicja struktury [line] przechowywującej informacje o wierszach */
typedef struct line {
  vector not_numbers;  // Wektor nieliczb czyli elementów typu [string]
  vector numbers;      // Wektor liczb czyli elementów typu [number]
  size_t nr;           // Numer wiersza - zgodny z kolejnością wczytywania
} line;

/* Funkcja zwracająca pustą linię */
line new_line();

/* Funkcja zwalniająca pamięć zalokowaną przez wektor lini */
void lines_delete(vector lines);

/* Funkcja wczytująca po kolei wszystkie wiersze. */
void get_input(vector* lines);

#endif /* LINES_H */