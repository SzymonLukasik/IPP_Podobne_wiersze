#define _GNU_SOURCE

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lines.h"
#include "parsing.h"
#include "safealloc.h"
#include "vector.h"

#define MIN_CHAR_VALUE 33
#define MAX_CHAR_VALUE 126
#define DELIMETERS " \t\n\v\f\r"

line new_line() {
  line new_line;
  vector v1, v2;
  v1 = new_vector();
  v2 = new_vector();
  new_line.not_numbers = v1;
  new_line.numbers = v2;
  return new_line;
}

/* Funkcja zwalniająca pamięć zalokowaną przez jedną linię */
static void line_delete(line l) {
  vector_delete(l.not_numbers);
  vector_delete(l.numbers);
}

void lines_delete(vector lines) {
  for (size_t i = 0; i < lines.size; i++)
    line_delete(*((line*)lines.data[i]));
  vector_delete(lines);
}

/* Funkcja sprawdza czy słowo jest liczbą czy nieliczbą,
a następnie dodaje je do lini */
static void add_word_to_line(string word, line* new_line) {
  number* n = (number*)safe_malloc(sizeof(number));

  if (word_to_number(word, n)) {
    vector_add(&new_line->numbers, n);
    free(word);
  } else {
    vector_add(&new_line->not_numbers, word);
    free(n);
  }
}

/* Jeśli wiersz jest pusty lub zawiera jedynie białe znaki
funkcja zwraca false, w przeciwnym przypadku funkcja zwraca true
i dodaje do nowej lini wszystkie słowa z wiersza */
static bool row_to_line(string row, line* new_line) {
  string token, word;

  token = strtok(row, DELIMETERS);

  if (token == NULL)
    return false;

  while (token != NULL) {
    word = (string)safe_calloc(strlen(token) + 1, sizeof(char));
    strcpy(word, token);
    add_word_to_line(word, new_line);
    token = strtok(NULL, DELIMETERS);
  }
  return true;
}

/* Funkcja sprawdza, czy wiersz jest poprawny czyli
czy nie zawiera niedozwolonych znaków */
static bool row_is_valid(string row, int row_length) {
  for (int i = 0; i < row_length && row[i] != '\n'; i++)
    if (row[i] == '\0' ||
        (strchr(DELIMETERS, row[i]) == NULL &&
         ((int)row[i] < MIN_CHAR_VALUE || (int)row[i] > MAX_CHAR_VALUE)))
      return false;
  return true;
}

/* Tworzy nową linię, umieszcza w niej zawartość wiersza i dodaje
ją do wektora lini */
static void add_line(vector* lines, string row, size_t line_nr) {
  line* new = (line*)safe_malloc(sizeof(line));
  *new = new_line();

  new->nr = line_nr;
  if (row_to_line(row, new))
    vector_add(lines, new);
  else {
    line_delete(*new);
    free(new);
  }
}

/* Jeśli wiersz reprezentowany w stringu [row]  jest błędny
funkcja wypisuje komunikat na wyjście diagnostyczne,
jeśli jest komentarzem funkcja go ignoruje, w przeciwnym razie
funkcja dodaje nową linię do wektora.  */
static void process_row(vector* lines,
                        string row,
                        int row_length,
                        size_t line_nr) {
  if (row[0] != '#') {
    if (row_is_valid(row, row_length))
      add_line(lines, row, line_nr);
    else
      fprintf(stderr, "ERROR %lu\n", line_nr);
  }
}

void get_input(vector* lines) {
  string row = NULL;
  size_t row_size = 0;
  size_t line_nr = 1;
  int row_length;
  errno = 0;

  do {
    row_length = getline(&row, &row_size, stdin);
    if (row_length != -1)
      process_row(lines, row, row_length, line_nr++);
    if (errno == ENOMEM)
      exit(1);
  } while (row_length != -1);
  free(row);
}