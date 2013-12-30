#ifndef PLIK_H
#define PLIK_H

#include "lista.h"
#include <stdio.h>

#define MAX_FILE_NAME 30

int czy_mtw(char *nazwa_pliku);
int czy_zapisac();
element * odczytaj_plik(element *first, char *nazwa_pliku);
int sprawdcz_czy_komentarz(FILE *plik);
int wyswietl_pliki();
int zapisz_plik(element *first, char *nazwa_pliku);

#endif // PLIK_H
