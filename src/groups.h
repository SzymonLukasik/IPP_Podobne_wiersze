#ifndef GROUPS_H
#define GROUPS_H

#include "vector.h"

/* Funkcja zwracająca wskaźnik do nowej grupy */
vector* new_group();

/* Funkcja wypisująca wynik działania programu. */
void print_groups(vector groups);

/* Funkcja zwalniająca pamięć zalokowaną przez wektor grup. */
void groups_delete(vector groups);

#endif /* GROUPS_H */