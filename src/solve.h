#ifndef SOLVE_H
#define SOLVE_H

#include "vector.h"

/* Funkcja iteruje się przez posortowany wektor lini i
porównując ze sobą poszczególne linie, tworzy wynikowy
wektor [groups] przetrzymujący wektory numerów wierszy podobnych. */
void make_groups(vector lines, vector* groups);

#endif /* SOLVE_H */