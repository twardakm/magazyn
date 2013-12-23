#ifndef TOWAR_H
#define TOWAR_H
#include "lista.h"

#define MAX_TOWAR_LENGHT 30

typedef struct towar
{
    char *nazwa;
    int ilosc;
    double cena;
} towar;

element * dodaj_towar(element *first);

#endif // TOWAR_H
