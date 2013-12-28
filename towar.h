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

    int czy_zmieniany; //0 gdy nie zmieniany, 1 - gdy zmieniony, bądź dodany
} towar;

int czy_zmieniono(element * first);
element * dodaj_towar(element *first);
element * sortowanie_cena_malejaco(element *first);
element * sortowanie_cena_rosnaco(element *first);
element * sortowanie_ilosc_malejaco(element *first);
element * sortowanie_ilosc_rosnaco(element *first);
element * sortowanie_nazwa_malejaco(element *first);
element * sortowanie_nazwa_rosnaco(element *first);
void wyswietl_towary(element *first);

#endif // TOWAR_H
