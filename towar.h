#ifndef TOWAR_H
#define TOWAR_H
#include "lista.h"

#define MAX_TOWAR_LENGHT 30

typedef struct towar
{
    char *nazwa_pliku;
    char *nazwa;
    int ilosc;
    double cena;
} towar;

element * dodaj_towar(element *first);
element * sortowanie_cena_malejaco(element *first);
element * sortowanie_cena_rosnaco(element *first);
element * sortowanie_ilosc_malejaco(element *first);
element * sortowanie_ilosc_rosnaco(element *first);
element * sortowanie_nazwa_rosnaco(element *first);
void wyswietl_towary(element *first);

#endif // TOWAR_H
