#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lines.h"
#include "parsing.h"
#include "vector.h"

#define FLOAT_SPECIAL_CHARS ".eEiI"

/* Funkcja sprawdza czy strtoll, strtoul lub strtold dokonały
interpretacji całego słowa. */
static bool whole_word_interpreted(string word, string endptr) {
  if (word[0] != '\0' && endptr[0] == '\0')
    return true;
  return false;
}

/* Funkcja sprawdza czy istnieją przesłanki aby wykluczyć
spośród baz w których może być zapisana liczba, bazy 8 i 16. */
static bool is_decimal(string word) {
  if (word[0] == '+' || word[0] == '-')
    return true;
  if ((strchr(word, '8') != NULL || strchr(word, '9') != NULL) &&
      (word[0] == '0' && (word[1] == 'x' || word[1] == 'X')) == false)
    return true;
  return false;
}

/* Funkcja rozważa sytuację gdy liczba jest typu long double,
ale można ją przedstawić jako liczbę całkowitą. */
static void check_if_integer(number* n) {
  if (floorl(n->val.ld) == n->val.ld && isfinite(n->val.ld)) {
    if (n->val.ld >= LLONG_MIN && n->val.ld <= LLONG_MAX) {
      n->val.ll = (long long)n->val.ld;
      n->type = LL;
    } else if (n->val.ld <= ULLONG_MAX && n->val.ld >= 0) {
      n->val.ul = (unsigned long)n->val.ul;
      n->type = UL;
    }
  }
}

/* Funkcja dokonuje próby konwersji słowa [word] na liczbę
typu oznaczonego przez [type] i zapisuje wynik w strukturze [*n] */
static void try_to_convert(string word,
                           num_type type,
                           number* n,
                           string* endptr) {
  errno = 0;
  int base = 0;

  if (is_decimal(word))
    base = 10;

  if (type == LL) {
    n->val.ll = strtoll(word, endptr, base);
    n->type = LL;
  } else if (type == UL) {
    n->val.ul = strtoul(word, endptr, base);
    n->type = UL;
  } else if (type == LD) {
    n->val.ld = strtold(word, endptr);
    n->type = LD;
    check_if_integer(n);
  }
}

/* Jeśli słowo zawiera znaki szczególne dla liczb zmiennoprzecinkowych oraz
nie zawiera ono podsłowa "0x" ani "0X", funkcja zwraca true.
W przeciwnym razie zwraca false.  */
static bool float_candidate(string word) {
  bool answer = false;
  for (int i = 0; word[i] != '\0'; i++) {
    if (strchr(FLOAT_SPECIAL_CHARS, word[i]) != NULL)
      answer = true;
    if ((word[i] == 'x' || word[i] == 'X'))
      if (i > 0 && word[i - 1] == '0') {
        answer = false;
        break;
      }
  }
  return answer;
}

/* Funkcja rozpatruje przypadek brzegowy gdy słowo powinno
być interpretowane jako 0 */
static bool check_edge_case(string word, number* n) {
  if (word[0] == '0' && (word[1] == 'x' || word[1] == 'X') && word[2] == '\0') {
    n->val.ll = 0;
    n->type = LL;
    return true;
  }
  return false;
}

/* Wiedząc, że słowo [word] to liczba niemieszcząca się w zakresie
typu long long, funkcja dobiera do niej odpowiedni typ liczbowy. */
static void choose_correct_type(string word, number* n, string* endptr) {
  if (n->val.ll == LLONG_MAX) {
    try_to_convert(word, UL, n, endptr);
    if (errno == ERANGE)
      try_to_convert(word, LD, n, endptr);
  } else if (n->val.ll == LLONG_MIN)
    try_to_convert(word, LD, n, endptr);
}

bool word_to_number(string word, number* n) {
  string endptr;

  if (check_edge_case(word, n))
    return true;

  if (float_candidate(word)) {
    try_to_convert(word, LD, n, &endptr);
    if (whole_word_interpreted(word, endptr))
      return true;
  } else {
    try_to_convert(word, LL, n, &endptr);
    if (whole_word_interpreted(word, endptr)) {
      if (errno == ERANGE)
        choose_correct_type(word, n, &endptr);
      return true;
    }
  }
  return false;
}