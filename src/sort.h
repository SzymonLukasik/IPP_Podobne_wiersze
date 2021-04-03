#ifndef SORT_H
#define SORT_H

#include "vector.h"

/* Funkcja definiująca porządek na zbiorze elementów typu [line],
porównująca linie, najpierw względem posortowanego wektora liczb [numbers],
następnie względem posortowanego wektora stringów [not_numbers]. */
int compare_line(const void* a, const void* b);

/* Funkcja sortująca wektor lini [lines]. */
void sort_lines(vector lines);

/* Funkcja sortująca wektor grup [groups] rosnąco względem namniejszego
numeru wiersza w grupie */
void sort_groups(vector grupy);

#endif /* SORT_H */