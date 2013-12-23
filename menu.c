#include "menu.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void tekst_powitalny(int ile)
{
    printf("\nMAGAZYN\n--------------------------------\n");
    printf("Towarów w magazynie: %d\n", ile);
    printf("1 - Dodaj towar\n");
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
            if(_DEBUG) printf("Wybrano %c",c);
            break;
        default:
            tekst_powitalny(size(lista));
            break;
        }
    }
}
