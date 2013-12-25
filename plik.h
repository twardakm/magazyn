#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include <stdio.h>

#define MAX_FILE_NAME 30

element * odczytaj_plik(element *first, char *nazwa_pliku);
int sprawdcz_czy_komentarz(FILE *plik);
int wyswietl_pliki();

#endif // PLIK_H
