# IPP_Podobne_wiersze

## Implementacja programu wyszukującego w tekście grupy wierszy podobnych.

Dokładna specyfikacja zadania jest opisana w pliku *problem_statement.md*

### Opis działania

Informacje o wierszach reprezentujemy w elementach typu [line],
które przetrzymujemy w dynamicznej tablicy. \
W czasie linearytmicznym względem wielkości wejścia porządkujemy
zawartość każdego wiersza oraz sortujemy wektor elementów typu [line]. \
Dzięki temu w czasie liniowym względem wielkości danych jesteśmy w stanie
dokonać podziału posortowanych wierszy na grupy wierszy podobnych. \
Następnie porządkujemy wektor grup zgodnie z poleceniem treści i
wypisujemy wynik.

### Struktura programu

Plik similar_lines korzysta z siedmiu bibliotek udostępniających:
    * safealloc.h - funkcje alokujące pamięć, które zwracają exit(1)
        w przypadku niepowodzenia.
    * vector.h - polimorficzne tablice dynamiczne służące
        do obsługi danych wejściowych i wynikowych.
    * lines.h - strukturę [line], obsługę wektorów elementów
         typu [line], wczytywanie wierszy i ich konwersję do [line].
    * parsing.h - zamianę słów na typy liczbowe.
    * groups.h - obługę wyniku w reprezentowanego w postaci
        wektorów wektorów liczb nieujemnych i jego wypisywanie
    * solve.h - funkcję, która dokonuje utworzenia podziału
        posortowanych wierszy na grupy wierszy podobnych.
    * sort.h - funkcje porównujące i sortujące elementy różnych
        typów: liczby, stringi, elementy typu [line] oraz
        wektory liczb nieujemnych (grupy podobnych wierszy).
