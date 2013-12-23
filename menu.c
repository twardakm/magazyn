#include "menu.h"
#include "lista.h"
#include "towar.h"
#include <stdio.h>
#include <stdlib.h>

void tekst_powitalny(int ile)
{
    printf("\nMAGAZYN\n--------------------------------\n");
    printf("Towarów w magazynie: %d\n", ile);
    printf("1 - Dodaj towar\n"
           "0 - Wyjdź\n");
}

void ustaw_kodowanie()
{
#ifdef WIN32
    system("chcp 65001");
#endif
}

element * wiadomosc_powitalna(element *lista)
{
    tekst_powitalny(size(lista));
    int c;

    while(c = getchar())
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = dodaj_towar(lista);
            break;
        case '0':
            if(_DEBUG) printf("Wybrano %c\n",c);
            printf("Dziękuję za skorzystanie z programu\nMarcin Twardak\n");
            return lista;
        default:
            tekst_powitalny(size(lista));
            break;
        }
    }
}
