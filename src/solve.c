#include <stdlib.h>

#include "groups.h"
#include "lines.h"
#include "safealloc.h"
#include "solve.h"
#include "sort.h"
#include "vector.h"

/* Funkcja sprawdza czy wiersz reprezentowany przez
[*curr_line] jest podobny do wiersza reprezentowanego przez [**base_line].
Jeśli tak, dodaje jego numer do grupy w której jest numer lini [**base_line].
Jeśli nie, przypisuje [**base_line] wartość [*curr_line] i dodaje do
nowej grupy jej numer. */
static void process_line(line** base_line,
                         line* curr_line,
                         vector** curr_group,
                         vector* groups) {
  size_t* nr = safe_malloc(sizeof(size_t));
  *nr = curr_line->nr;

  if (compare_line(base_line, &curr_line) == 0)
    vector_add(*curr_group, nr);
  else {
    *base_line = curr_line;
    *curr_group = new_group();
    vector_add(groups, *curr_group);
    vector_add(*curr_group, nr);
  }
}

void make_groups(vector lines, vector* groups) {
  if (lines.size > 0) {
    line* base_line = ((line*)lines.data[0]);
    size_t i = 0;
    vector* curr_group = new_group();
    vector_add(groups, curr_group);

    while (i < lines.size) {
      process_line(&base_line, (line*)lines.data[i], &curr_group, groups);
      i++;
    }
  }
}