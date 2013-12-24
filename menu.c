#include "menu.h"
#include "lista.h"
#include "towar.h"
#include "plik.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tekst_powitalny(int ile)
{
    printf("\nMAGAZYN\n--------------------------------\n");
    wyswietl_date();
    printf("Towarów w magazynie: %d\n", ile);
    printf("1 - Dodaj towar\n"
           "2 - Wczytaj plik\n"
           "3 - Wyświetl dodane towary\n"
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
        case '2':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = odczytaj_plik(lista, NULL);
            break;
        case '3':
            if(_DEBUG) printf("Wybrano %c\n",c);
            wyswietl_towary(lista);
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

void wyswietl_date()
{
    time_t *tp = malloc(sizeof(time_t));
    time(tp); //wygenerowanie czasu

    printf("%s\n", ctime(tp));

    free(tp);
}
