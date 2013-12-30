#ifndef TOWAR_H
#define TOWAR_H
#include "lista.h"

#define MAX_TOWAR_LENGHT 30
#define MAX_COLOR_LENGHT 15

typedef struct towar
{
    char *nazwa_pliku;
    char *nazwa;
    int ilosc;
    int rozmiar;
    char *kolor;
    double cena;

    int czy_zmieniany; //0 gdy nie zmieniany, 1 - gdy zmieniony, bądź dodany
} towar;

int czy_zmieniono(element * first);
element * dodaj_sztuk_towaru(element *first);
element * dodaj_towar(element *first);
element * przyjeto_towar(element *first);
element * sortowanie_cena_malejaco(element *first);
element * sortowanie_cena_rosnaco(element *first);
element * sortowanie_ilosc_malejaco(element *first);
element * sortowanie_ilosc_rosnaco(element *first);
element * sortowanie_nazwa_malejaco(element *first);
element * sortowanie_nazwa_rosnaco(element *first);
element * sprzedanie_towaru(element *first);
void tekst_przyjeto_towar();
void wyswietl_rozmiary();
void wyswietl_towary(element *first, int * ktory, int ile);
void wyszukiwanie_towaru(element *first);

#endif // TOWAR_H
