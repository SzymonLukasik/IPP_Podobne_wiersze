#include "groups.h"
#include "lines.h"
#include "solve.h"
#include "sort.h"
#include "vector.h"

/* **********************OPIS_DZIAŁANIA*****************************
Informacje o wierszach reprezentujemy w elementach typu [line],
które przetrzymujemy w dynamicznej tablicy.
W czasie linearytmicznym względem wielkości wejścia porządkujemy
zawartość każdego wiersza oraz sortujemy wektor elementów typu [line].
Dzięki temu w czasie liniowym względem wielkości danych jesteśmy w stanie
dokonać podziału posortowanych wierszy na grupy wierszy podobnych.
Następnie porządkujemy wektor grup zgodnie z poleceniem treści i
wypisujemy wynik.
****************************************************************** */

/* ***********************STRUKTURA_PROGRAMU***********************
Plik similar_lines korzysta z siedmiu bibliotek udostępniających:
    x safealloc.h - funkcje alokujące pamięć, które zwracają exit(1)
        w przypadku niepowodzenia.
    x vector.h - polimorficzne tablice dynamiczne służące
        do obsługi danych wejściowych i wynikowych.
    x lines.h - strukturę [line], obsługę wektorów elementów
        typu [line], wczytywanie wierszy i ich konwersję do [line].
    x parsing.h - zamianę słów na typy liczbowe.
    x groups.h - obługę wyniku w reprezentowanego w postaci
        wektorów wektorów liczb nieujemnych i jego wypisywanie
    x solve.h - funkcję, która dokonuje utworzenia podziału
        posortowanych wierszy na grupy wierszy podobnych.
    x sort.h - funkcje porównujące i sortujące elementy różnych
        typów: liczby, stringi, elementy typu [line] oraz
        wektory liczb nieujemnych (grupy podobnych wierszy).
****************************************************************** */

int main(void) {
  vector lines = new_vector();
  vector groups = new_vector();

  get_input(&lines);

  sort_lines(lines);
  make_groups(lines, &groups);
  sort_groups(groups);

  print_groups(groups);

  lines_delete(lines);
  groups_delete(groups);
}