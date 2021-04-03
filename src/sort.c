#include <stdlib.h>
#include <strings.h>

#include "lines.h"
#include "sort.h"
#include "vector.h"

/* ****************************************************************
Funkcje związane z sortowaniem elementów składających się na linię,
czyli wektorów liczb [numbers] i wektorów stringów [not_numbers].
**************************************************************** */

/* Funkcja definiująca porządek częściowy na zbiorze elementów
typu [number].
Liczby typu [long double] są większe od liczb innych typów.
Liczby typu [unsigned long] są większe od liczb typu [long long]
Jeśli reprezentowane liczby są tego samego typu o ich porządku
decyduje standardowa relacja <= obowiązująca w danym typie. */
static int compare_number(const void* a, const void* b) {
  number arg1 = **(number**)a;
  number arg2 = **(number**)b;

  if ((arg1.type == LL || arg1.type == UL) && arg2.type == LD)
    return -1;
  if (arg1.type == LD && (arg2.type == LL || arg2.type == UL))
    return 1;

  if (arg1.type == LL && arg2.type == UL)
    return -1;
  if (arg1.type == UL && arg2.type == LL)
    return 1;

  if (arg1.type == LL) {
    if (arg1.val.ll < arg2.val.ll)
      return -1;
    if (arg1.val.ll > arg2.val.ll)
      return 1;
  }
  if (arg1.type == UL) {
    if (arg1.val.ul < arg2.val.ul)
      return -1;
    if (arg1.val.ul > arg2.val.ul)
      return 1;
  }
  if (arg1.type == LD) {
    if (arg1.val.ld < arg2.val.ld)
      return -1;
    if (arg1.val.ld > arg2.val.ld)
      return 1;
  }
  return 0;
}

/* Funkcja definiująca porządek leksykograficzny na zbiorze stringów. */
static int compare_str(const void* a, const void* b) {
  string arg1 = *(string*)a;
  string arg2 = *(string*)b;

  return strcasecmp(arg1, arg2);
}

/* Funkcja sortująca wektor elementów typu [number] */
static void sort_numbers(vector numbers) {
  qsort(numbers.data, numbers.size, sizeof(number*), compare_number);
}

/* Funkcja sortująca wektor elementów typu [string] */
static void sort_not_numbers(vector not_numbers) {
  qsort(not_numbers.data, not_numbers.size, sizeof(string), compare_str);
}

/* Funkcja sortująca wektory [l.numbers] i [l.not_numbers] lini [l] */
static void sort_line(line l) {
  sort_numbers(l.numbers);
  sort_not_numbers(l.not_numbers);
}

/* Funkcja sortująca wektory [l.numbers] i [l.not_numbers] dla każdej
lini [l] zawartej w wektorze lini [lines]. */
static void sort_each_line(vector lines) {
  for (size_t i = 0; i < lines.size; i++)
    sort_line(*((line*)lines.data[i]));
}

/* ****************************************************************
Funkcje związane z porównywaniem poszczególnych lini
oraz sortowaniem wektora lini
**************************************************************** */

/* Funkcja porównująca leksykograficznie posortowane wektory
elementów typu [number] */
static int compare_numbers(const vector a, const vector b) {
  size_t i = 0;

  while (i < a.size && i < b.size &&
         compare_number(&a.data[i], &b.data[i]) == 0)
    i++;
  if (i == a.size || i == b.size) {
    if (a.size < b.size)
      return -1;
    if (a.size > b.size)
      return 1;
    return 0;
  }
  if (compare_number(&a.data[i], &b.data[i]) == -1)
    return -1;
  return 1;
}

/* Funkcja porównująca leksykograficznie posortowane wektory
elementów typu [string] */
static int compare_not_numbers(const vector a, const vector b) {
  size_t i = 0;

  while (i < a.size && i < b.size &&
         strcasecmp((string)a.data[i], (string)b.data[i]) == 0)
    i++;
  if (i == a.size || i == b.size) {
    if (a.size < b.size)
      return -1;
    if (a.size > b.size)
      return 1;
    return 0;
  }
  return strcasecmp((string)a.data[i], (string)b.data[i]);
}

int compare_line(const void* a, const void* b) {
  line line1 = **(line**)a;
  line line2 = **(line**)b;

  int cmp_numbers = compare_numbers(line1.numbers, line2.numbers);
  if (cmp_numbers == 0)
    return compare_not_numbers(line1.not_numbers, line2.not_numbers);
  else
    return cmp_numbers;
}

void sort_lines(vector lines) {
  sort_each_line(lines);
  qsort(lines.data, lines.size, sizeof(line*), compare_line);
}

/* ***************************************************************
Funkcje związane z porównywaniem poszczególnych grup
i sorotwaniem wektora grup.
**************************************************************** */

/* Funkcja porównująca elementy typu size_t */
static int compare_size_t(const void* a, const void* b) {
  size_t arg1 = **(size_t**)a;
  size_t arg2 = **(size_t**)b;

  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}

/* Funkcja sortująca grupę ze względu na numery wierszy
do niej należących */
static void sort_group(vector group) {
  qsort(group.data, group.size, sizeof(size_t*), compare_size_t);
}

/* Funkcja sortująca rosnąco każdą grupę zawartą w wektorze grup [groups] */
static void sort_each_group(vector groups) {
  for (size_t i = 0; i < groups.size; i++)
    sort_group(*((vector*)groups.data[i]));
}

/* Funkcja porównująca grupy posortowane wcześniej przez funkcję [sort_group]
względem ich pierwszego elementu (czyli też najmniejszego wiersza w grupie). */
static int compare_group(const void* a, const void* b) {
  vector gr1 = **(vector**)a;
  vector gr2 = **(vector**)b;

  return compare_size_t(&gr1.data[0], &gr2.data[0]);
}

void sort_groups(vector groups) {
  sort_each_group(groups);
  qsort(groups.data, groups.size, sizeof(vector*), compare_group);
}